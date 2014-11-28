// DeplicateHandle.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

void ReadFromTheFileMapping(HANDLE hFileMap)
{
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	
	HANDLE hFileMapRW = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 10240, NULL);

	HANDLE hFileMapRO;
	DuplicateHandle(::GetCurrentProcess(), hFileMapRW, GetCurrentProcess(), &hFileMapRO, FILE_MAP_READ, FALSE, 0);
	
	ReadFromTheFileMapping(hFileMapRO);

	CloseHandle(hFileMapRW);
	CloseHandle(hFileMapRO);

	return 0;
}



