#include <windows.h>
#include <iostream>
using namespace std;

void ShowProcessors()
{
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION pBuffer = NULL;
	DWORD dwSize = 0;
	DWORD procCoreCount = 0;

	BOOL bResult = GetLogicalProcessorInformation(pBuffer, &dwSize);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		cout << "impossible get processors info" << endl;
	}
	pBuffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(dwSize);
	bResult = GetLogicalProcessorInformation(pBuffer, &dwSize);
	if (!bResult)
	{
		free(pBuffer);
		return;
	}
	DWORD lpiCount = dwSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
	for (DWORD current = 0;current < lpiCount;current++)
	{
		if (pBuffer[current].Relationship == RelationProcessorCore)
		{
			if (pBuffer[current].ProcessorCore.Flags == 1)
			{
				cout << "one cpu core" << endl;
			}
			else
			{
				cout << "one cpu socket" << endl;
			}
			procCoreCount++;
		}
	}

	cout << "core sum:" << procCoreCount << endl;
	free(pBuffer);
}

void main()
{
	ShowProcessors();
	system("pause");
	BOOL bIsWow = FALSE;
	if (!IsWow64Process(GetCurrentProcess(), &bIsWow))
	{
		cout << "IsWow64Process invoke fail" << endl;
	}
}