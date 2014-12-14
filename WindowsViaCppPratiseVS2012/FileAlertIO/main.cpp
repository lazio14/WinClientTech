#include <windows.h>
#include <iostream>
using namespace std;

VOID WINAPI APCFunc(ULONG_PTR dwParam)
{

}

DWORD WINAPI ThreadFunc(PVOID pvParam)
{
	HANDLE hEvent = (HANDLE)pvParam;
	DWORD dw = WaitForSingleObjectEx(hEvent, INFINITE, TRUE);
	switch (dw)
	{
	case WAIT_OBJECT_0:
		cout << "thread:WAIT_OBJECT_0" << endl;
		break;
	case WAIT_IO_COMPLETION:
		// QueueUserAPC forceed us out of a wait state
		cout << "Thread WAIT_IO_COMPLETION" << endl;
		return 0;
	default:
		break;
	}
	return 0;
}

void main()
{
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread = CreateThread(NULL, 0, ThreadFunc, (PVOID)hEvent, 0, NULL);
	// SetEvent(hEvent);
	system("pause");
	QueueUserAPC(APCFunc, hThread, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hEvent);
	system("pause");
}