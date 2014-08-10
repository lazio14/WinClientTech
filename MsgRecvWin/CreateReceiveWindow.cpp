#include <tchar.h>
#include <windows.h>
#include <iostream>
using namespace std;

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	TCHAR szText[MAX_PATH] = {0};
	_stprintf(szText, _T("wParam=%d lParam=%d"), wParam, lParam);

	switch(message)
	{
	case WM_USER + 100:
		OutputDebugString(_T("WM_USER + 100"));
		OutputDebugString(szText);
		return 0;
	case WM_USER + 200:
		OutputDebugString(_T("WM_USER + 200"));
		OutputDebugString(szText);
		PostQuitMessage(0);
		return 0;
	default:
		OutputDebugString(_T("default"));		
		OutputDebugString(szText);
		break;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,					
					PSTR szCmdLine, int iCmdShow)					
{
	HWND hWnd = CreateWindow(
		_T("static"),
		_T("MsgRecv"),
		WS_OVERLAPPEDWINDOW,,		
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,		
		NULL,		
		NULL,		
		NULL);
	
	if(hWnd != NULL && IsWindow(hWnd))
	{
		SetWindowLong(hWnd, GWL_WNDPROC, (LONG) WndProc);				
	}

	MSG msg;
	while (GetMessage (&msg, NULL, 0, 0))		
	{
		TranslateMessage (&msg);		
		DispatchMessage (&msg);		
	}	
	return msg.wParam;
}
