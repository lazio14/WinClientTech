#include <windows.h>
#include <iostream>
using namespace std;

#define SHARE_MEMORY_NAME TEXT("MMFSharedData")

void main()
{
	HANDLE g_hFileMap = NULL;
	int nOpt = 0;
	cin >> nOpt;
	if (nOpt == 0) // 创建共享内存
	{
		g_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4 * 1024, SHARE_MEMORY_NAME);
		if (g_hFileMap != NULL)
		{
			if (GetLastError() == ERROR_ALREADY_EXISTS)
			{
				cout << "Mapping already exists" << endl;
				CloseHandle(g_hFileMap);
				system("pause");
				return;
			}
			else
			{
				PVOID pView = MapViewOfFile(g_hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
				if (pView != NULL)
				{
					PCHAR pAnsiChar = (PCHAR)pView;
					strcpy(pAnsiChar, "this is a string");
					UnmapViewOfFile(pView);
				}
				else
				{
					cout << "can't map view of file" << endl;
				}
				system("pause");
				CloseHandle(g_hFileMap);
			}
		}
		else
		{
			cout << "create file mapping fail" << endl;
		}
	}
	else // 读共享内存
	{
		HANDLE hFileMapT = OpenFileMapping(FILE_MAP_READ| FILE_MAP_WRITE, FALSE, SHARE_MEMORY_NAME);
		if (hFileMapT != NULL)
		{
			PVOID pView = MapViewOfFile(hFileMapT, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			if (pView != NULL)
			{
				PCHAR pAnsiChar = (PCHAR)pView;
				cout << pAnsiChar << endl;
				UnmapViewOfFile(pView);
			}
			else
			{
				cout << "map view fial " << endl;
			}
			CloseHandle(hFileMapT);
		}
		else
		{
			cout << "Can't open file mapping" << endl;
		}		
	}
	system("pause");
}