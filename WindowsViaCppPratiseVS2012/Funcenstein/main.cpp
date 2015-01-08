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

int funcenstein4()
{
	__try
	{
		return 1;
	}
	__finally
	{
		return 2;
	}
	return 3;
}

DWORD Funcarama4()
{
	DWORD dwResult = 0;
	__try
	{
		__leave;
		cout << "Fun4 try" << endl;
		dwResult = 1;
	}
	__finally
	{
		cout << "func4 finally" << endl;
	}
	return dwResult;
}

DWORD AbnormalTerminatinFalseTest()
{
	__try
	{

	}
	__finally
	{
		cout << "AbnormalTerminatinTest False: " << AbnormalTermination() << endl;
	}
	return 0;
}

DWORD AbnormalTerminatinTrueTest()
{
	__try
	{
		return 0;
	}
	__finally
	{
		cout << "AbnormalTerminatinTest TRUE: " << AbnormalTermination() << endl;
	}
}

void main()
{
	cout << FuncaDoodleDoo() << endl;
	cout << funcenstein4() << endl;
	cout << Funcarama4() << endl;

	AbnormalTerminatinTrueTest();
	AbnormalTerminatinFalseTest();
	system("pause");	

}