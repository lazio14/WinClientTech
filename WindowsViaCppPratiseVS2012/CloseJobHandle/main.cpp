#include <windows.h>

int main()
{
	HANDLE hJob = CreateJobObject(NULL, TEXT("lazio14"));
	::AssignProcessToJobObject(hJob, GetCurrentProcess());
	CloseHandle(hJob);
	hJob = OpenJobObject(JOB_OBJECT_ALL_ACCESS, FALSE, TEXT("lazio14"));
	DWORD dwError = GetLastError();

	return 0;
}