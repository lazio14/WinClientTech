#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;
void main()
{
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	TCHAR szCmd[MAX_PATH] = {0};
	_tcscpy(szCmd, TEXT("notepad"));
	BOOL bRet = CreateProcess(NULL, szCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	//DWORD dwRet = WaitForSingleObject((HANDLE)444, 1000); // dwRet must be WAIT_FAILED
	DWORD dwRet = WaitForSingleObject(pi.hProcess, 3000);
	switch (dwRet)
	{
	case WAIT_OBJECT_0:
		cout << "object 0" << endl;
		break;
	case WAIT_TIMEOUT:
		cout << "time out" << endl;
		break;
	case WAIT_FAILED:
		cout << "fail" << endl;
		break;
	default:
		break;
	}
	CloseHandle(pi.hProcess);
	system("pause");
}