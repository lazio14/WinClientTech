#include <windows.h>
#include <iostream>
#include <interlockedapi.h>
using namespace std;

long g_x = 0;
unsigned int g_fResourceInUse = 0;

void AccessRes()
{
	for (int i = 0;i < 100;i++)
	{
		cout << i << endl;
	}
}

DWORD WINAPI ThreadFunc1(LPVOID pvParam)
{
	// g_x++;
	InterlockedExchangeAdd(&g_x, 1);
	while (InterlockedExchange(&g_fResourceInUse, 1) == 1)
	{
		Sleep(0);
	}
	AccessRes();
	InterlockedExchange(&g_fResourceInUse, 0);
	return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID pvParam)
{
	// g_x++;
	InterlockedExchangeAdd(&g_x, 1);
	while (InterlockedExchange(&g_fResourceInUse, 1) == 1)
	{
		Sleep(0);
	}
	AccessRes();
	InterlockedExchange(&g_fResourceInUse, 0);
	return 0;
}

void main()
{
	HANDLE hThreadd1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
	CloseHandle(hThreadd1);

	HANDLE hThreadd2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
	CloseHandle(hThreadd2);

	system("pause");
	cout << "g_x:" << g_x << endl;


	system("pause");
}