#include<windows.h>
#include<tchar.h>
#include<iostream>
using namespace std;

int main()
{
	HWND hWnd = ::FindWindow(_T("static"), _T("MsgRecv"));
	if (hWnd)
	{
		for (int i = 1; i <= 100; i++)
		{
			::SendMessage(hWnd, WM_USER + 100, WPARAM(i), NULL);		
			Sleep(10);
		}				
		::SendMessage(hWnd, WM_USER + 200, NULL, NULL);

		cout << "finish send" << endl;
	}
	else
	{
		cout << "hwnd is null" << endl;
	}
	return 0;
}
