#include <windows.h>
#include <iostream>
using namespace std;

UINT Sum(UINT uNum)
{
	return (uNum == 0 ? 0 : uNum + Sum(uNum - 1));
}

LONG WINAPI FilterFunc(DWORD dwExceptionCode)
{
	return ((dwExceptionCode == STATUS_STACK_OVERFLOW) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH);
}

DWORD WINAPI SumThreadFunc(PVOID pvParam)
{
	UINT uSumNum = PtrToUlong(pvParam);
	UINT uSum = UINT_MAX;

	__try
	{
		uSum = Sum(uSumNum);
	}
	__except(FilterFunc(GetExceptionCode()))
	{
		cout << "exception" << endl;
	}
	return uSum;
}

void main()
{
	UINT uSum = 5000;
	HANDLE hThread = CreateThread(NULL, 0, SumThreadFunc, (PVOID)uSum, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, (PDWORD)&uSum);
	if (uSum == UINT_MAX)
	{
		cout << "THE NUM IS TOO BIG" << endl;
	}
	else
	{
		cout << "success" << endl;
	}

	CloseHandle(hThread);
	system("pause");
}