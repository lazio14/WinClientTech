#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include <afxres.h>
#define IDC_MAIN_EDIT	101
#define IDC_MAIN_TOOL   102
#define IDC_MAIN_STATUS 103

#define TOOLBAR_BTN_SUM 3

const char g_szClassName[] = "myWindowClass";
TBBUTTON tbb[TOOLBAR_BTN_SUM];
TBADDBITMAP tbab;

BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR pszFileName)
{
    HANDLE hFile;
    BOOL bSuccess = FALSE;
	
    hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        DWORD dwTextLength;
		
        dwTextLength = GetWindowTextLength(hEdit);
        // No need to bother if there's no text.
        if(dwTextLength > 0)
        {
            LPSTR pszText;
            DWORD dwBufferSize = dwTextLength + 1;
			
            pszText = (char *)GlobalAlloc(GPTR, dwBufferSize);
            if(pszText != NULL)
            {
                if(GetWindowText(hEdit, pszText, dwBufferSize))
                {
                    DWORD dwWritten;
					
                    if(WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
                        bSuccess = TRUE;
                }
                GlobalFree(pszText);
            }
        }
        CloseHandle(hFile);
    }
    return bSuccess;
}


BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName)
{
    HANDLE hFile;
    BOOL bSuccess = FALSE;
	
    hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, 0, NULL);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        DWORD dwFileSize;
		
        dwFileSize = GetFileSize(hFile, NULL);
        if(dwFileSize != 0xFFFFFFFF)
        {
            LPSTR pszFileText;
			
            pszFileText = (char*)GlobalAlloc(GPTR, dwFileSize + 1);
            if(pszFileText != NULL)
            {
                DWORD dwRead;
				
                if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
                {
                    pszFileText[dwFileSize] = 0; // Add null terminator
                    if(SetWindowText(hEdit, pszFileText))
                        bSuccess = TRUE; // It worked!
                }
                GlobalFree(pszFileText);
            }
        }
        CloseHandle(hFile);
    }
    return bSuccess;
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
	case WM_CREATE:
		{
			HFONT hfDefault = NULL;
			HWND hEdit = NULL;

			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""),
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
				0, 0, 100, 100, hwnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
			if (!hEdit)
			{
				MessageBox(hwnd, TEXT("could not create edit box"), TEXT("error"), MB_OK | MB_ICONERROR);
			}

			hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_FILE_OPEN_TEST:
				{
					OPENFILENAME ofn;
					TCHAR szFileName[MAX_PATH] = {0};
					
					ZeroMemory(&ofn, sizeof(ofn));
					
					ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
					ofn.hwndOwner = hwnd;
					ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
					ofn.lpstrFile = szFileName;
					ofn.nMaxFile = MAX_PATH;
					ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
					ofn.lpstrDefExt = "txt";
					
					if(GetOpenFileName(&ofn))
					{
						// Do something usefull with the filename stored in szFileName 
						HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
						LoadTextFileToEdit(hEdit, ofn.lpstrFile);
					}
				}				
				break;			
			case ID_FILE_SAVE_TEST:
				{
					OPENFILENAME ofn;
					TCHAR szFileName[MAX_PATH] = {0};
					
					ZeroMemory(&ofn, sizeof(ofn));
					
					ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
					ofn.hwndOwner = hwnd;
					ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
					ofn.lpstrFile = szFileName;
					ofn.nMaxFile = MAX_PATH;
					ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
					ofn.lpstrDefExt = "txt";
					
					if(GetOpenFileName(&ofn))
					{
						// Do something usefull with the filename stored in szFileName 
						HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
						SaveTextFileFromEdit(hEdit, ofn.lpstrFile);
					}
				}
				break;
			}
		}
		break;	
	case WM_SIZE:
		{
// 			HWND hEdit;
// 			RECT rcClient;
// 
// 			GetClientRect(hwnd, &rcClient);
// 			hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
// 			SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
			HWND hTool;
			RECT rcTool;
			int nToolHeight = 0;

			HWND hStatus;
			RECT rcStatus;
			int nStatusHeight = 0;

			HWND hEdit;
			RECT rcEdit;
			int nEditHeigth;

			hTool = GetDlgItem(hwnd, IDC_MAIN_TOOL);
			SendMessage(hTool, TB_AUTOSIZE, 0, 0);
			GetClientRect(hTool, &rcTool);
			nToolHeight = rcTool.bottom - rcTool.top;

			hStatus = GetDlgItem(hwnd, IDC_MAIN_STATUS);
			SendMessage(hStatus, WM_SIZE, 0, 0);
			GetClientRect(hStatus, &rcStatus);
			nStatusHeight = rcStatus.bottom - rcStatus.top;

			RECT rcClient;
			GetClientRect(hwnd, &rcClient);

			hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
			SetWindowPos(hEdit, NULL, 0, nToolHeight, rcClient.right, rcClient.bottom - nToolHeight - nStatusHeight, SWP_NOZORDER);
		}
		break;
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
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	
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

	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
        hwnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);

	// Send the TB_BUTTONSTRUCTSIZE message, which is required for
	// backward compatibility.
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_SMALL_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);

	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_FILE_NEW;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_FILE_OPEN_TEST;//ID_FILE_OPEN;

	tbb[2].iBitmap = STD_FILESAVE;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_FILE_SAVE_TEST;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(tbb[0]), (LPARAM)&tbb);


	HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
		0, 0, 0, 0, hwnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
	
	int statwidths[] = {200, -1};
	SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths) / sizeof(statwidths[0]), (LPARAM)statwidths);
	SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("hi there"));

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