#include <windows.h>
#include <iostream>
using namespace std;

const int n64K = 65536;

void main()
{
	HANDLE hFile =CreateFile(TEXT("biggerThan64k.tmp"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "error" << endl;
		return;
	}

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);\

	PBYTE pbFile1 = (PBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
	PBYTE pbFile2 = (PBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, n64K, 0);

	int nDifference = int(pbFile2 - pbFile1);
	cout << nDifference << endl;

	int nZeroOffset = 5;
	PSTR pchAnsi2 = (PSTR)pbFile2;
	//cout << pchAnsi2 << endl;
	pchAnsi2[nZeroOffset] = 0;
	cout << pchAnsi2 << endl;
	
	PSTR pchAnsi1 = (PSTR)pbFile1;
	cout << pchAnsi1 + n64K << endl;

	UnmapViewOfFile(pbFile1);
	UnmapViewOfFile(pbFile2);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);
	system("pause");
}