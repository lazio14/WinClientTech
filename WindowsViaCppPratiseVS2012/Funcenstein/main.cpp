#include <windows.h>
#include <iostream>
using namespace std;

HANDLE g_sem = NULL;

DWORD WINAPI ChildThread(LPVOID pvParam)
{
	WaitForSingleObject(g_sem, INFINITE);
	cout << "child thread" << endl;
	return 0;
}

int funcenstein()
{
	ReleaseSemaphore(g_sem, 1, NULL);
	int retVal = 5;
	__try
	{
		WaitForSingleObject(g_sem, INFINITE);
		PVOID p = NULL;
		int a = *(int *)p;
		cout << "ok" << endl;
	}
	__finally
	{
		ReleaseSemaphore(g_sem, 1, NULL);
	}

	return retVal;
}

void main()
{
	g_sem = CreateSemaphore(NULL, 0, 1, NULL);
	cout << funcenstein() << endl;
	CreateThread(NULL, 0, ChildThread, NULL, 0, NULL);
	system("pause");
	
}