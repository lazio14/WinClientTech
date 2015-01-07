#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	DWORD dwTlsIdx = 0;
	dwTlsIdx = TlsAlloc();
	if (TlsGetValue(dwTlsIdx) == NULL)
	{
		TlsSetValue(dwTlsIdx, HeapAlloc(GetProcessHeap(), 0, MAX_PATH));
		char* p = (char*)TlsGetValue(dwTlsIdx);
		strcpy(p, "this is a string");
		cout << (char*)TlsGetValue(dwTlsIdx) << endl;
		TlsFree(dwTlsIdx);
	}
	else
	{
		cout << "error" << endl;
	}

	dwTlsIdx = TlsAlloc();
	if (TlsGetValue(dwTlsIdx) == NULL)
	{
		cout << "ok" << endl;
	}

	system("pause");
}