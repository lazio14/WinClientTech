// WriteFileByInheritHandle.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
/*
	�ó��򼯳ɸ����̵��ļ��ں˶���
	ͨ�������л�ȡ�ļ������������д�ļ��Ĳ�����
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



