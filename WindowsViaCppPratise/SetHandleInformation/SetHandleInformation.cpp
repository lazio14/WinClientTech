// SetHandleInformation.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = FALSE;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	HANDLE hFile=CreateFile("test.txt",GENERIC_WRITE,FILE_SHARE_READ,&sa, 
		OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//先创建一个空的文件			

	// 将hFile以继承方式传递给一个进程后，
	// 创建的第二个进程，不再需要继承这个内核对象时，可以关掉。
	SetHandleInformation(hFile, HANDLE_FLAG_INHERIT, 0);

	DWORD dwFlags = 0;
	GetHandleInformation(hFile, &dwFlags);
	BOOL bInherit = (0  != (dwFlags & HANDLE_FLAG_INHERIT));


	// 再以继承方式创建其他进程时，不会再继承hFile
	SetHandleInformation(hFile, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
	CloseHandle(hFile); // 这里在调试模式下一定会异常，运行时，只会返回false。

	
	return 0;
}



