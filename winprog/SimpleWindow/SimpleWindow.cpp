#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
    {
	case WM_INITDIALOG:
        return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}        
		break;
        default:
            return FALSE;
    }
    return TRUE;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
	case WM_CLOSE:
		DestroyWindow(hwnd);
        break;
	case WM_DESTROY:
		PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		{
			TCHAR szModuleName[MAX_PATH] = {0};
			HINSTANCE hInstance = GetModuleHandle(NULL);
			GetModuleFileName(hInstance, szModuleName, MAX_PATH);
			MessageBox(hwnd, szModuleName, TEXT("Note"), MB_OK);
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_FILE_EXIT:
				PostQuitMessage(0);
				break;
			}
			case ID_STUFF_GO:
				int nRet = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
				break;
			break;
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
	
    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
	
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);
	
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
	
    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}