#include <windows.h>
#include <iostream>
using namespace std;

DWORD WINAPI ChildThread(LPVOID pvParam)
{
	while (TRUE)
	{
		cout << 1 << endl;
	}
	return 0;
}

void main()
{
	DWORD dwPriority = GetPriorityClass(GetCurrentProcess());
	if (dwPriority == NORMAL_PRIORITY_CLASS)
	{
		::MessageBox(NULL, TEXT("OK"), TEXT("TIP"), MB_OK);
	}
	system("pause");
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	system("pause");

	HANDLE hThread = CreateThread(NULL, 0, ChildThread, NULL, CREATE_SUSPENDED, NULL);
	DWORD dwThreadPriority = GetThreadPriority(hThread);
	SetThreadPriority(hThread, THREAD_PRIORITY_IDLE);
	ResumeThread(hThread);
	CloseHandle(hThread);
	system("pause");
}