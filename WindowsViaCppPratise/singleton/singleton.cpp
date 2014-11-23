// singleton.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	HANDLE h = CreateMutex(NULL, FALSE, TEXT("{THIS IS A UNIQE STRING}"));
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		MessageBox(NULL, TEXT("already running"), TEXT("WARNING"), MB_OK);
		CloseHandle(h);
		return 0;
	}

	Sleep(1000000);
	CloseHandle(h);
	return 0;
}