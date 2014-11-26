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

	HANDLE hNotExistHandle = OpenMutex(NULL, FALSE, TEXT("{this is not exist handle}"));
	if (hNotExistHandle == NULL)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			MessageBox(NULL, TEXT("the handle not exist"), TEXT("WARNING"), MB_OK);
		}
	}
	else
	{
		CloseHandle(hNotExistHandle);
	}

	HANDLE hOtherTypeHandle = CreateFileMapping((HANDLE)0xFFFFFFFF,NULL, PAGE_READWRITE,0,1024,TEXT("{THIS IS A UNIQE STRING}"));

	if (hOtherTypeHandle == NULL)
	{
		if (GetLastError() == ERROR_INVALID_HANDLE)
		{
			MessageBox(NULL, TEXT("handle type not match"), TEXT("WARNING"), MB_OK);
		}
	}

	
	Sleep(1000000);
	CloseHandle(h);
	return 0;
}