#include "splashwin.h"

#include <stdio.h>

LRESULT CALLBACK WndProcSplash(HWND, UINT, WPARAM, LPARAM);
HBITMAP Picture;
BITMAP qBITMAP;

HANDLE createSplash(HINSTANCE hInst, HWND pWnd, char * fName) {
  WNDCLASS wnd;
  wnd.style = CS_HREDRAW | CS_VREDRAW;
  wnd.lpfnWndProc = WndProcSplash;
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hInstance = hInst;
  wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
  wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
  wnd.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wnd.lpszMenuName = NULL;                     //no menu
  wnd.lpszClassName = TEXT("ProgrammStarterSplashWin");
  if(!RegisterClass(&wnd)) {
    MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
    return 0;
  }
  HWND hwnd;

  Picture = (HBITMAP)LoadImage(NULL,fName, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  if (Picture == 0) return 0;

  int iRet = GetObject(reinterpret_cast<HGDIOBJ>(Picture), sizeof(BITMAP),reinterpret_cast<LPVOID>(&qBITMAP));
  if (!iRet) return 0;

  RECT rc;
  GetWindowRect(GetDesktopWindow(), &rc);

  hwnd = CreateWindowEx(0 ,
                        TEXT("ProgrammStarterSplashWin"),
                        "",
                        WS_VISIBLE ,
                        (rc.right)/2,
                        (rc.bottom)/2,
                        qBITMAP.bmWidth,
                        qBITMAP.bmHeight,
                        pWnd,
                        NULL,
                        hInst,
                        NULL);
  DWORD tmp = GetWindowLongA( hwnd, GWL_STYLE );
  tmp &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
  SetWindowLongA( hwnd, GWL_STYLE, tmp );
  SetWindowPos( hwnd, 0, 0,0, qBITMAP.bmWidth, qBITMAP.bmHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
  return hwnd;
}

LRESULT CALLBACK WndProcSplash(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
  switch (msg) {
    case WM_PAINT: {
      hdc = BeginPaint(hwnd, &ps);
      HDC hLocalDC = CreateCompatibleDC(hdc);
      if (hdc != NULL) {
        HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, Picture);
        if (hOldBmp != 0) {
          bool qRet = BitBlt(hdc, 0, 0, qBITMAP.bmWidth, qBITMAP.bmHeight, hLocalDC, 0, 0, SRCCOPY);
          if (qRet) {
            SelectObject(hLocalDC, hOldBmp);
            DeleteDC(hLocalDC);
          }
        }
      }
      EndPaint(hwnd, &ps);
      break;
    }
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
