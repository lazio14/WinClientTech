#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;

void SuspendProcess(DWORD dwProcessID, BOOL fSuspend)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessID);

	if (hSnapShot != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 te = {sizeof(te)};
		BOOL fOk = Thread32First(hSnapShot, &te);
		for (;fOk;fOk = Thread32Next(hSnapShot, &te))
		{
			if (te.th32OwnerProcessID == dwProcessID)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
				if (hThread != NULL)
				{
					if (fSuspend)
					{
						SuspendThread(hThread);
					}
					else
					{
						ResumeThread(hThread);
					}
					CloseHandle(hThread);
				}
			}
		}
		CloseHandle(hSnapShot);
	}
}

DWORD WINAPI ChildThread(LPVOID pvParam)
{
	int* pVal = (int *)pvParam;
	while (true)
	{
		cout << *pVal << endl;
	}
	return 0;
}

void main()
{
// 	int val1 = 1;
// 	int val2 = 2;
// 	DWORD thread1Id = 0;
// 	DWORD thread2Id = 0;
// 	HANDLE h1 = CreateThread(NULL, 0, ChildThread, &val1, 0, &thread1Id);
// 	HANDLE h2 = CreateThread(NULL, 0, ChildThread, &val2, 0, &thread2Id);
// 	system("pause");
// 
// 	SuspendThread(h1);
// 	SuspendThread(h2);
// 	CloseHandle(h1);
// 	CloseHandle(h2);
// 	system("pause");
// 	SuspendProcess(GetProcessId(GetCurrentProcess()), TRUE);

	DWORD dwProcessID = 5980;
	SuspendProcess(dwProcessID, TRUE);
	system("pause");
	SuspendProcess(dwProcessID, FALSE);
 	system("pause");
}