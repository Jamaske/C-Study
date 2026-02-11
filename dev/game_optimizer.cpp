// GameAffinitySetter.cpp
// Builds: cl /EHsc /O2 GameAffinitySetter.cpp

#include <windows.h>
#include <tlhelp32.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <bitset>

/*
Valid priority classes for processes:
- REALTIME_PRIORITY_CLASS
- HIGH_PRIORITY_CLASS
- ABOVE_NORMAL_PRIORITY_CLASS
- NORMAL_PRIORITY_CLASS
- BELOW_NORMAL_PRIORITY_CLASS
- IDLE_PRIORITY_CLASS
*/

constexpr const wchar_t* DEFAULT_TARGET_EXE = L"SolarlandClient-Win64-Shipping.exe";  // Change this to your actual game exe
constexpr DWORD TARGET_PRIORITY = HIGH_PRIORITY_CLASS;
constexpr int MINIMAL_THREAD_COUNT = 11;
constexpr int CORE_UNUSED = 0;
constexpr int TIMEOUT_MS = 10000;
constexpr int POLL_INTERVAL_MS = 50;

DWORD_PTR calculate_affinity_mask() {
    static constexpr DWORD_PTR t2 = 0xFFFFFFFFFFFFFFFF, t1 = 0x5555555555555555;
    static constexpr int thread_unused = 2 * CORE_UNUSED;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int tr = sysInfo.dwNumberOfProcessors - thread_unused;
    DWORD_PTR mask = (t1 | (t2 << 2 * (tr - MINIMAL_THREAD_COUNT)));
    return (mask << thread_unused) & ~(t2 << sysInfo.dwNumberOfProcessors);
}

DWORD find_process_id(const wchar_t* exe_name) {
    PROCESSENTRY32W entry = {};
    entry.dwSize = sizeof(entry);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(entry.szExeFile, exe_name) == 0) {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        } while (Process32NextW(snapshot, &entry));
    }
    CloseHandle(snapshot);
    return 0;
}

void patch_process(DWORD pid, DWORD_PTR affinityMask) {
    HANDLE hProc = OpenProcess(PROCESS_SET_INFORMATION | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!hProc) {
        std::cerr << "Failed to open process " << pid << " Error: " << GetLastError() << std::endl;
        return;
    }

    if (!SetPriorityClass(hProc, TARGET_PRIORITY))
        std::cout << "Failed to set priority. Error: " << GetLastError() << std::endl;
    else
        std::cout << "Priority set successfully." << std::endl;

    if (!SetProcessAffinityMask(hProc, affinityMask)) {
        std::cout << "Failed to set affinity. Error: " << GetLastError() << std::endl;
    } else {
        // validate affinity is set
        DWORD_PTR systemMask = 0, processMask = 0;
        if (!GetProcessAffinityMask(hProc, &processMask, &systemMask)) {
            std::cerr << "Unable to get process affinity mask: " << GetLastError() << std::endl;
            CloseHandle(hProc);
            return;
        }
        if (processMask == affinityMask) {
            std::cout << "Affinity set successfully." << std::endl;
        } else {
            std::cerr << "Affinity failed to apply." << std::endl;
        }
    }
    CloseHandle(hProc);
}

int main() {
    auto start_time = std::chrono::steady_clock::now();
    DWORD pid = 0;

    DWORD_PTR affinity = calculate_affinity_mask();
    std::cout << "Calculated Affinity Mask: " << std::bitset<32>(affinity) << std::endl;

    std::wcout << L"Waiting for start of " << DEFAULT_TARGET_EXE << std::endl;
    while (true) {
        pid = find_process_id(DEFAULT_TARGET_EXE);
        if (pid) break;
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        if (duration > TIMEOUT_MS) {
            std::cerr << "Timed out waiting after " << duration << "ms" << std::endl;
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(POLL_INTERVAL_MS));
    }

    patch_process(pid, affinity);

    return 0;
}
