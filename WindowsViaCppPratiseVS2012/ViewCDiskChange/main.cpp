#include <windows.h>
void main()
{
	HANDLE hFile = CreateFile(TEXT("MMFTest.dat"),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 100, NULL);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
}
