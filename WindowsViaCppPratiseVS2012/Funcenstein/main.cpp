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

DWORD FuncaDoodleDoo() 
{
	DWORD dwTemp = 0;
	while (dwTemp < 10)
	{
		__try
		{
			if (dwTemp == 2)
			{
				continue;
			}
			if (dwTemp == 3)
			{
				break;
			}
		}
		__finally
		{
			dwTemp++;
		}
		dwTemp++;
	}
	dwTemp += 10;
	return dwTemp;
}

void main()
{
	cout << FuncaDoodleDoo() << endl;
	system("pause");
	
}