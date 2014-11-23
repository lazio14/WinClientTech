// CreateInheritHandle.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// 创建一个文件句柄，并继承给创建的进程。
	// 通过命令行把文件句柄传递给WriteFileByInheritHandle

	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	HANDLE hFile=CreateFile("test.txt",GENERIC_WRITE,FILE_SHARE_READ,&sa, 
		OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//先创建一个空的文件

	TCHAR szCmd[MAX_PATH] = {0};
	TCHAR szWriteFileExeName[MAX_PATH] = {0};
	_tcscpy(szWriteFileExeName, TEXT("WriteFileByInheritHandle.exe"));
	_stprintf(szCmd,_T("%s %d"), szWriteFileExeName, hFile);        //句柄转换成字符串


	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	BOOL bRet = CreateProcess(szWriteFileExeName, szCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (bRet != FALSE)
	{
		// success
		::MessageBox(NULL, TEXT("Create Process success"), TEXT("tip"), MB_OK);
	}
	else
	{
		int errID = GetLastError();
		TCHAR szErrorInfo[MAX_PATH] = {0};
		_stprintf(szErrorInfo, TEXT("error:%d"), errID);
		::MessageBox(NULL, szErrorInfo, TEXT("tip"), MB_OK);
	}
	CloseHandle(hFile);
	return 0;
}



