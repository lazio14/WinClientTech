// WriteFileByInheritHandle.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
/*
	该程序集成父进程的文件内核对象。
	通过命令行获取文件句柄，并进行写文件的操作。
*/
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	HANDLE hFile = 0;
	_stscanf(lpCmdLine, TEXT("%d"), &hFile);

	TCHAR szBuf[MAX_PATH] = {0};
	_stprintf(szBuf, TEXT("this is a buffer writed by WriteFileByInheriteHandle EXE.\nHandle = 0x%x"), hFile);
	DWORD dwWriteSize = 0;
	BOOL ret = WriteFile(hFile, szBuf, sizeof(szBuf), &dwWriteSize, NULL);
	if (ret)
	{
		::MessageBox(NULL, TEXT("success"), TEXT("Tip"), MB_OK);
	}
	else
	{
		::MessageBox(NULL, TEXT("Fail"), TEXT("Tip"), MB_OK);
	}
	CloseHandle(hFile);
	return 0;
}



