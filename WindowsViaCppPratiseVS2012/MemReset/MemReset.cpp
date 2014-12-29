#include <windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

void main()
{
	TCHAR szTestData[] = TEXT("TEST DATA");
	PTSTR pszData = (PTSTR)VirtualAlloc(NULL, 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	_tcscpy_s(pszData, 1024, szTestData);

	if (MessageBox(NULL, TEXT("DO YOU WANT TO ACCESS THIS DATA LATER?"), szTestData, MB_YESNO) == IDNO)
	{
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery(pszData, &mbi, sizeof(mbi));
		VirtualAlloc(pszData, mbi.RegionSize, MEM_RESET, PAGE_READWRITE);
	}

	MEMORYSTATUS mst;
	GlobalMemoryStatus(&mst);
	DWORD dwProcessAddr = mst.dwTotalPhys / 4;

	PVOID pvDummy = VirtualAlloc(NULL, dwProcessAddr, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	if (pvDummy)
	{
		ZeroMemory(pvDummy, dwProcessAddr);
	}

	if (_tcscmp(pszData, szTestData) == 0)
	{
		cout << "modified data page was EXIST" << endl;
	}
	else
	{
		cout << "modified data page was NOT EXIST" << endl;
	}

	if (pvDummy)
	{
		VirtualFree(pvDummy, 0, MEM_RELEASE);
	}
	VirtualFree(pszData, 0, MEM_RELEASE);
}