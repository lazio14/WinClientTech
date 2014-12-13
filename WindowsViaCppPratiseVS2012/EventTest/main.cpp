#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;
HANDLE g_hEvent;
DWORD WINAPI WordCount(PVOID pvParam)
{
	WaitForSingleObject(g_hEvent, INFINITE);
	for (int i = 0; i < 100; i++)
	{
		cout << i << endl;
	}
	SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI SpellCheck(PVOID pvParam)
{
	WaitForSingleObject(g_hEvent, INFINITE);
	for (int i = 100; i < 200; i++)
	{
		cout << i << endl;
	}
	SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI GrammarCheck(PVOID pvParam)
{
	WaitForSingleObject(g_hEvent, INFINITE);
	for (int i = 200; i < 300; i++)
	{
		cout << i << endl;
	}
	SetEvent(g_hEvent);
	return 0;
}

void main()
{
	//g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread[3];
	DWORD dwThreadId = 0;
	hThread[0] = CreateThread(NULL, 0, WordCount, NULL, 0, &dwThreadId);
	hThread[1] = CreateThread(NULL, 0, SpellCheck, NULL, 0, &dwThreadId);
	hThread[2] = CreateThread(NULL, 0, GrammarCheck, NULL, 0, &dwThreadId);

	system("pause");
	SetEvent(g_hEvent);
	system("pause");

}