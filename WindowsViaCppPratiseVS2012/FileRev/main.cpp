#include <windows.h>
#include <iostream>
using namespace std;
void main()
{
	// 假设文件是纯Ascii编码的文件。
	HANDLE hFile = CreateFile(TEXT("filerec.txt"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "file not open" << endl;
		return;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	
	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwFileSize + sizeof(CHAR), NULL);
	

	PVOID pvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (NULL == pvFile)
	{
		CloseHandle(hFileMap);
		return;
	}
	CloseHandle(hFileMap);

	PSTR pchAnsi = (PSTR)pvFile;
	pchAnsi[dwFileSize / sizeof(CHAR)] = 0;
	_strrev(pchAnsi);

	UnmapViewOfFile(pvFile);

	// 为了去除末尾的NULL占位符
	SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
	SetEndOfFile(hFile);
	CloseHandle(hFile);

}