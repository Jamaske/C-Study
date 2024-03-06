// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <tchar.h>
#define BUFFER_SIZE 1024
using namespace std;


struct Buffer {
	Buffer* prev = nullptr;
	size_t current = sizeof(Buffer);
	size_t size = 0;
};

class Allocator {
	Buffer* some_buffer = nullptr;
public:


	~Allocator() {
		while (some_buffer != nullptr) {
			Buffer* prev = some_buffer->prev;
			free(some_buffer);
			some_buffer = prev;
		}
	}

	void createNewBuffer(size_t size){
		Buffer* New = (Buffer*)malloc(size + sizeof(Buffer));
		new (New) Buffer();
		New->prev = some_buffer;
		New->size = size + sizeof(Buffer);
		some_buffer = New;
	}

	Allocator() {
		createNewBuffer(BUFFER_SIZE);
	}

	char* allocate(size_t size) {
		if (some_buffer->size - some_buffer->current < size) {
			createNewBuffer(max<size_t>(size, BUFFER_SIZE));
		}

		char* ret = ((char*)some_buffer) + some_buffer->current;
		some_buffer->current = some_buffer->current + size;
		return ret;
	}
	void deallocate(void*) {

	}
};

Allocator allocator2024;

class CStringComparator
{
public:

	/*
		A < B --> true
	*/
	bool operator()(const char* A, const char* B) const
	{
		while (true)
		{
			if (A[0] == B[0])
			{
				//A = B
				if (!A[0])
					return false;

				A++;
				B++;
			}
			else
			{
				return A[0] < B[0];
			}
		}
	}
};

template <class T>
class CMyAllocator {
public:
	typedef typename T value_type;

	CMyAllocator()
	{

	}

	template <class U>
	CMyAllocator(const CMyAllocator<U>& V)
	{

	}

	T* allocate(size_t Count) {
		//printf("Allocate %d\n", (int)(Count * sizeof(T)));
		//return (T*)malloc(sizeof(T) * Count);
		return (T*)allocator2024.allocate(sizeof(T) * Count);
	}

	void deallocate(T* V, size_t Count)
	{
		//printf("Free %d\n", (int)(Count * sizeof(T)));
		allocator2024.deallocate(V);
		//free(V);
	}
};

bool cmp(pair<const char*, int> First, pair<const char*, int> Second) {
	return First.second > Second.second;
}

void TextMapTest()
{
	map<const char*, size_t, CStringComparator, CMyAllocator<char*>> Map;
	const wchar_t* file_name = L"C:/Users/AlexanderBorisovich/source/repos/ConsoleApplication1/ConsoleApplication1/test.txt";
	HANDLE hFile = CreateFile(file_name,               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile");
		_tprintf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), file_name);
		return;
	}
	LARGE_INTEGER file_size;
	bool get_size = GetFileSizeEx(hFile, &file_size);
	if (!get_size)
	{
		printf("GetFileSizeEx");
		_tprintf(TEXT("Terminal failure: unable to get file size \"%s\" for read.\n"), file_name);
		return;
	}
	//BUFFERSIZE = file_size;
	DWORD  dwBytesRead = 0;
	char*  ReadBuffer = (char*)malloc(file_size.QuadPart + 1);
	OVERLAPPED ol = { 0 };
	printf("file_size is: %d\n\r", (int)file_size.QuadPart);

	const char* Words[] = { "Who", "Are", "You", "Who" };
	const char* Word;
	DWORD bytes_read = 0;
	bool OK = ReadFile(hFile, ReadBuffer, file_size.QuadPart, &bytes_read, 0);
	if (!OK) {
		printf("Unable to read file\n");
		return;
	}
	if (bytes_read != file_size.QuadPart) {
		printf("Bytes read isn't equal to file size\n");
		return;
	}
	ReadBuffer[file_size.QuadPart] = '\0';
	printf("bytes_read: %d\n", bytes_read);
	int len_word = 0;
	for (int i = 0; i < bytes_read; i++) {
		if ((unsigned char)ReadBuffer[i] > 32) len_word++;
		else {
			if (len_word == 0)
				continue;
			ReadBuffer[i] = '\0';
			char* Word = &ReadBuffer[i - len_word];
			auto It = Map.find(Word);
			if (It == Map.end())
				Map.insert(make_pair(Word, 1));
			else
				It->second++;
			len_word = 0;
		}
	}
	vector<pair<const char*, int>> statistics;
	
	for (auto Entry : Map) {
		//printf("Word %s, count %I64d\n", Entry.first, (uint64_t)Entry.second);
		statistics.push_back(Entry);
	}
	sort(statistics.begin(), statistics.end(), cmp);

	for (int i = 0; i < min<size_t>(10, statistics.size()); i++) {
		printf("Word %s, count %I64d\n", statistics[i].first, (uint64_t)statistics[i].second);
	}
	printf("\n");
	
	CloseHandle(hFile);

}

#include <windows.h>

ULONGLONG GetCurrentTimeMs()
{
	SYSTEMTIME S = { 0 };
	FILETIME F = { 0 };
	GetSystemTime(&S);
	SystemTimeToFileTime(&S, &F);
	LARGE_INTEGER Int;
	Int.HighPart = F.dwHighDateTime;
	Int.LowPart = F.dwLowDateTime;
	return Int.QuadPart / 10000;
}


int main()
{
	ULONGLONG Start = GetCurrentTimeMs();

	TextMapTest();

	ULONGLONG End = GetCurrentTimeMs();

	printf("Time (ms) %d\n", (int)(End - Start));

	getchar();

	//C++, where is your LinkedHashMap?
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
