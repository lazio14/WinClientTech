#include <windows.h>
void main()
{
	BOOL bProcessBoost =  TRUE;
	BOOL bThreadBoost = TRUE;
	GetProcessPriorityBoost(GetCurrentProcess(), &bProcessBoost);
	GetThreadPriorityBoost(GetCurrentThread(), &bThreadBoost);
}