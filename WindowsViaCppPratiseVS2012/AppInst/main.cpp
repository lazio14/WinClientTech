#include <windows.h>
#include <iostream>
using namespace std;

#pragma data_seg("Shared")
UINT g_lApplicationInstances = 0;
#pragma data_seg()

#pragma comment(linker, "/Section:Shared,RWS")


void main()
{
	InterlockedExchangeAdd(&g_lApplicationInstances, 1);
	cout << g_lApplicationInstances << endl;
	system("pause");
}