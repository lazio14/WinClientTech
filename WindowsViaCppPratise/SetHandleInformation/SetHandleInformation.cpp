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
		OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//�ȴ���һ���յ��ļ�			

	// ��hFile�Լ̳з�ʽ���ݸ�һ�����̺�
	// �����ĵڶ������̣�������Ҫ�̳�����ں˶���ʱ�����Թص���
	SetHandleInformation(hFile, HANDLE_FLAG_INHERIT, 0);

	DWORD dwFlags = 0;
	GetHandleInformation(hFile, &dwFlags);
	BOOL bInherit = (0  != (dwFlags & HANDLE_FLAG_INHERIT));


	// ���Լ̳з�ʽ������������ʱ�������ټ̳�hFile
	SetHandleInformation(hFile, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
	CloseHandle(hFile); // �����ڵ���ģʽ��һ�����쳣������ʱ��ֻ�᷵��false��

	
	return 0;
}



