#include "windows.h"
#include <tchar.h>
#include <Strsafe.h>

void StartRestrictedProcess()
{
	BOOL bInJob = FALSE;
	IsProcessInJob(GetCurrentProcess(), NULL, &bInJob);
	if (bInJob)
	{
		::MessageBox(NULL, TEXT("process already in job"), TEXT("TIP"), MB_OK);
		return;
	}
	else
	{
		::MessageBox(NULL, TEXT("OK"), TEXT("TIP"), MB_OK);
	}

	HANDLE hjob = CreateJobObject(NULL, TEXT("RestrictedProcessJob"));
	JOBOBJECT_BASIC_LIMIT_INFORMATION jobli = {0};
	jobli.PriorityClass = IDLE_PRIORITY_CLASS;
	jobli.PerProcessUserTimeLimit.QuadPart = 10000;
	jobli.LimitFlags = JOB_OBJECT_LIMIT_PRIORITY_CLASS | JOB_OBJECT_LIMIT_JOB_TIME;
	SetInformationJobObject(hjob, JobObjectBasicLimitInformation, &jobli, sizeof(jobli));

	JOBOBJECT_BASIC_UI_RESTRICTIONS jobuir;
	jobuir.UIRestrictionsClass = JOB_OBJECT_UILIMIT_NONE;
	jobuir.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_EXITWINDOWS;
	jobuir.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_HANDLES;
	SetInformationJobObject(hjob, JobObjectBasicUIRestrictions, &jobuir, sizeof(jobuir));

	STARTUPINFO si = {sizeof(si)};
	PROCESS_INFORMATION pi;
	TCHAR szCmdLine[8] = {0};
	_tcscpy_s(szCmdLine, _countof(szCmdLine), TEXT("CMD"));
	BOOL bResult = CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	AssignProcessToJobObject(hjob, pi.hProcess);
	ResumeThread(pi.hThread);
	CloseHandle(pi.hThread);

	HANDLE h[2];
	h[0] = pi.hProcess;
	h[1] = hjob;
	DWORD dw = WaitForMultipleObjects(2, h, FALSE, INFINITE);
	switch (dw - WAIT_OBJECT_0)
	{
	case 0:
		::MessageBox(NULL, TEXT("The Process has terminated"), TEXT("TIP"), MB_OK);
		break;
	case 1:
		::MessageBox(NULL, TEXT("All of the Job's allotted CPU time was used"), TEXT("TIP"), MB_OK);
		break;
	default:
		::MessageBox(NULL, TEXT("Default"), TEXT("TIP"), MB_OK);
		break;
	}

	FILETIME CreateionTime;
	FILETIME ExitTime;
	FILETIME KernelTime;
	FILETIME UserTime;
	TCHAR szInfo[MAX_PATH] = {0};
	GetProcessTimes(pi.hProcess, &CreateionTime, &ExitTime, &KernelTime, &UserTime);
	StringCchPrintf(szInfo, _countof(szInfo), TEXT("Kernel = %u | Uer = %u\n"),
		KernelTime.dwLowDateTime / 10000, UserTime.dwLowDateTime / 10000);
	MessageBox(GetActiveWindow(), szInfo, TEXT("Restricted Process times"), 
		MB_ICONINFORMATION | MB_OK);

	CloseHandle(hjob);
	CloseHandle(pi.hProcess);

}

int main()
{
	StartRestrictedProcess();
	return 0;
}