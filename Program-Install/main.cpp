#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "resource.h"
#include "init.h"
//#include "run.h"


HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
//////////////////////////////////////////////////////////////
    WNDCLASS wnd;
    wnd.style = CS_HREDRAW | CS_VREDRAW; //we will explain this later
    wnd.lpfnWndProc = WndProc;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hInstance = hInstance;
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
    wnd.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wnd.lpszMenuName = NULL;                     //no menu
    wnd.lpszClassName = TEXT("ProgramInstall");
    if(!RegisterClass(&wnd))
    {
        MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
        return 0;
    }
//////////////////////////////////////////////////////////////
    hInst=hInstance;
//////////////////////////////////////////////////////////////
    MSG msg;
    HWND hwnd;

    RECT rc;
    GetWindowRect(GetDesktopWindow(), &rc);

    hwnd = CreateWindowEx(WS_EX_DLGMODALFRAME ,
                          TEXT("ProgramInstall"),
                          TEXT("Program Install"),
                          WS_VISIBLE | WS_SYSMENU | WS_CAPTION ,
                          (rc.right-400)/2,
                          (rc.bottom-300)/2,
                          400,
                          300,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    ShowWindow(hwnd, SW_SHOW);              //display the window on the SW_SHOW
//////////////////////////////////////////////////////////////
//    if(init(hwnd) == -1)
//    {
//        MessageBox(NULL, "Can not find language files! File is corrupt.", "Error", MB_OK);
//    }
//
//////////////////////////////////////////////////////////////
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
    {
        SendMessage(hwnd, (UINT)WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(ICON_MAIN)));
        init(hwnd);
        return 0;
    }
    case WM_INITDIALOG:
    {
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_COMMAND:
    {
      if (lParam == (LPARAM)CButton->Wnd) {
        SendMessage(hwnd, WM_DESTROY, 0, 0);
      }

    }
   case WM_TIMER:{
     switch (wParam) {
       case TIMER_START: {
         KillTimer(hwnd,TIMER_START);
         init_second(hwnd);
         return 0;
       }
     }
   }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
