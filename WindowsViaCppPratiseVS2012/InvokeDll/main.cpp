#include <windows.h>
using namespace std;


DWORD WINAPI ChildThread(LPVOID pvParam)
{

	OutputDebugString(TEXT("================InvokeDll ChildThread================"));
	return 0;
}



int main()
{
	DWORD dwError = 0;
	HINSTANCE  hDll = LoadLibrary(L"DLLDemo.dll");
	if (hDll == NULL)
	{
		dwError = GetLastError();
	}

	CreateThread(NULL, 0, ChildThread, NULL, 0, NULL);
	system("pause");
}