// inherite.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "inherite.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	STARTUPINFO si = {sizeof(si)};
	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB, piProcessC;

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;

	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, _countof(szPath), TEXT("ProcessB"));
	CreateProcess(NULL, szPath, &saProcess, &saThread, FALSE, 0, NULL, NULL,&si, &piProcessB);

	_tcscpy_s(szPath, _countof(szPath), TEXT("ProcessC"));
	CreateProcess(NULL, szPath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &piProcessC);

	return 0;
}