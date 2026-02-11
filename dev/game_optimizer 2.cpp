#include <windows.h>
#include <comdef.h>
#include <initguid.h>
#include <Wbemidl.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>


constexpr DWORD TARGET_PRIORITY = REALTIME_PRIORITY_CLASS;

DWORD_PTR get_physical_core_affinity_mask() {
    DWORD length = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &length);

    std::vector<BYTE> buffer(length);
    auto* info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.data());

    if (!GetLogicalProcessorInformationEx(RelationProcessorCore, info, &length)) {
        std::wcerr << L"Failed to query processor info. Error: " << GetLastError() << std::endl;
        return 0;
    }

    DWORD_PTR mask = 0;
    for (BYTE* ptr = buffer.data(); ptr < buffer.data() + length;) {
        auto* core = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(ptr);
        if (core->Relationship == RelationProcessorCore) {
            KAFFINITY coreMask = core->Processor.GroupMask[0].Mask;
            if (coreMask & 1) coreMask &= ~1ULL;  // Remove core 0
            mask |= coreMask;
        }
        ptr += core->Size;
    }
    return mask;
}

void patch_process(DWORD pid, DWORD_PTR affinityMask) {
    HANDLE hProc = OpenProcess(PROCESS_SET_INFORMATION | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!hProc) {
        std::wcerr << L"Failed to open process " << pid << L". Error: " << GetLastError() << std::endl;
        return;
    }

    if (SetPriorityClass(hProc, TARGET_PRIORITY))
        std::wcout << L"Priority set to REALTIME." << std::endl;
    else
        std::wcerr << L"Failed to set priority. Error: " << GetLastError() << std::endl;

    if (SetProcessAffinityMask(hProc, affinityMask))
        std::wcout << L"Affinity set successfully." << std::endl;
    else
        std::wcerr << L"Failed to set affinity. Error: " << GetLastError() << std::endl;

    CloseHandle(hProc);
}

int main(int argc, char* argv[]) {
    wchar_t targetExeBuffer[MAX_PATH];
    const wchar_t* targetExe = L"Game.exe";
    if (argc >= 2) {
        size_t converted = 0;
        mbstowcs_s(&converted, targetExeBuffer, argv[1], MAX_PATH - 1);
        targetExe = targetExeBuffer;
    }
    DWORD_PTR affinityMask = get_physical_core_affinity_mask();
    if (affinityMask == 0) {
        std::wcerr << L"Could not determine affinity mask." << std::endl;
        return 1;
    }

    HRESULT hr;
    hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr)) return 1;

    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
                              RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0, NULL);
    if (FAILED(hr)) return 1;

    IWbemLocator* pLocator = nullptr;
    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
                          IID_IWbemLocator, (LPVOID*)&pLocator);
    if (FAILED(hr)) return 1;

    IWbemServices* pServices = nullptr;
    hr = pLocator->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, 0, 0, 0, &pServices);
    if (FAILED(hr)) return 1;

    hr = CoSetProxyBlanket(pServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE,
                           NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hr)) return 1;

    IEnumWbemClassObject* pEnumerator = nullptr;
    hr = pServices->ExecNotificationQuery(
        _bstr_t("WQL"),
        _bstr_t("SELECT * FROM __InstanceCreationEvent WITHIN 0.1 WHERE TargetInstance ISA 'Win32_Process'"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL, &pEnumerator);

    if (FAILED(hr)) return 1;

    std::wcout << L"Waiting for process: " << targetExe << std::endl;

    while (true) {
        IWbemClassObject* pEvent = nullptr;
        ULONG returned = 0;

        HRESULT hr = pEnumerator->Next(-1, 1, &pEvent, &returned);
        if (SUCCEEDED(hr) && returned) {
            VARIANT varInstance;
            hr = pEvent->Get(L"TargetInstance", 0, &varInstance, NULL, NULL);
            if (SUCCEEDED(hr) && (varInstance.vt == VT_UNKNOWN)) {
                IWbemClassObject* pInstance = nullptr;
                varInstance.punkVal->QueryInterface(IID_IWbemClassObject, (void**)&pInstance);
                VariantClear(&varInstance);

                VARIANT varName, varPID;
                pInstance->Get(L"Name", 0, &varName, NULL, NULL);
                pInstance->Get(L"ProcessId", 0, &varPID, NULL, NULL);

                if (_wcsicmp(varName.bstrVal, targetExe) == 0) {
                    DWORD pid = varPID.uintVal;
                    patch_process(pid, affinityMask);
                    VariantClear(&varName);
                    VariantClear(&varPID);
                    pInstance->Release();
                    pEvent->Release();
                    break;
                }

                VariantClear(&varName);
                VariantClear(&varPID);
                pInstance->Release();
            }
            pEvent->Release();
        }
    }

    pEnumerator->Release();
    pServices->Release();
    pLocator->Release();
    CoUninitialize();
    return 0;
}
