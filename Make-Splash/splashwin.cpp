#include "splashwin.h"

#include <stdio.h>

LRESULT CALLBACK WndProcSplash(HWND, UINT, WPARAM, LPARAM);
HBITMAP Picture;
BITMAP qBITMAP;
HFONT fontbig;
HFONT fontsmall;
char * prglabel = NULL;
char * versionlabel = NULL;
char * messagelabel = NULL;
HBITMAP lPic = 0;
BITMAP qlBITMAP;
HBITMAP rPic = 0;
BITMAP qrBITMAP;

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
  fontbig = CreateFont (-MulDiv(25, GetDeviceCaps(GetDC(0), LOGPIXELSY), 72), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
	  OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	  DEFAULT_PITCH | FF_DONTCARE, "Tahoma");
  fontsmall = CreateFont (-MulDiv(10, GetDeviceCaps(GetDC(0), LOGPIXELSY), 72), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
	  OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	  DEFAULT_PITCH | FF_DONTCARE, "Tahoma");
  return hwnd;
}

LRESULT CALLBACK WndProcSplash(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
  char text[] =  "rest";
  switch (msg) {
    case WM_PAINT: {
      hdc = BeginPaint(hwnd, &ps);
      HDC hLocalDC = CreateCompatibleDC(hdc);
      if (hdc != NULL) {
        HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, Picture);
        if (hOldBmp != 0) {
          bool qRet = BitBlt(hdc, 0, 0, qBITMAP.bmWidth, qBITMAP.bmHeight, hLocalDC, 0, 0, SRCCOPY);
          if (prglabel != NULL) {
            HFONT hFont = (HFONT)SelectObject(hLocalDC, fontbig);
            SetTextColor(hLocalDC, RGB(255,255,0));
            SetBkMode(hLocalDC, TRANSPARENT);
            TextOut(hLocalDC, 60, 70, prglabel, strlen(prglabel));
            SelectObject(hLocalDC, hFont);
          }
          if (versionlabel != NULL) {
            HFONT hFont = (HFONT)SelectObject(hLocalDC, fontsmall);
            SetTextColor(hLocalDC, RGB(255,255,0));
            SetBkMode(hLocalDC, TRANSPARENT);
            TextOut(hLocalDC, 65, 110, versionlabel, strlen(versionlabel));
            SelectObject(hLocalDC, hFont);
          }
          if (messagelabel != NULL) {
            HFONT hFont = (HFONT)SelectObject(hLocalDC, fontsmall);
            SetTextColor(hLocalDC, RGB(255,255,0));
            SetBkMode(hLocalDC, TRANSPARENT);
            TextOut(hLocalDC, 65, 255, messagelabel, strlen(messagelabel));
            SelectObject(hLocalDC, hFont);
          }
          if (lPic != 0) {
            HBITMAP hlOldBmp = (HBITMAP)SelectObject(hLocalDC, lPic);
            BitBlt(hdc, 65, 130, qlBITMAP.bmWidth, qlBITMAP.bmHeight, hLocalDC, 0, 0, SRCCOPY);
            SelectObject(hLocalDC, hlOldBmp);
          }
          if (rPic != 0) {
            HBITMAP hlOldBmp = (HBITMAP)SelectObject(hLocalDC, rPic);
            BitBlt(hdc, qBITMAP.bmWidth-qrBITMAP.bmWidth-65, 130, qrBITMAP.bmWidth, qrBITMAP.bmHeight, hLocalDC, 0, 0, SRCCOPY);
            SelectObject(hLocalDC, hlOldBmp);
          }
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

int setPrgLabel(char * label) {
  if (prglabel != NULL) delete[] prglabel;
  prglabel = new char[MAX_PATH];
  memcpy(prglabel, label, strlen(label)+1);
  return 0;
}

int setVersiomLabel(char * label) {
  if (versionlabel != NULL) delete[] versionlabel;
  versionlabel = new char[MAX_PATH];
  memcpy(versionlabel , label, strlen(label)+1);
  return 0;
}

int setMessageLabel(char * label) {
  if (messagelabel != NULL) delete[] messagelabel;
  messagelabel = new char[MAX_PATH];
  memcpy(messagelabel , label, strlen(label)+1);
  return 0;
}

int setLeftPic(char * filename) {
  lPic = (HBITMAP)LoadImage(NULL,filename, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  if (lPic == 0) return 0;
  int iRet = GetObject(reinterpret_cast<HGDIOBJ>(lPic), sizeof(BITMAP),reinterpret_cast<LPVOID>(&qlBITMAP));
  if (!iRet) lPic=0;
  return 0;
}

int setRightPic(char * filename) {
  rPic = (HBITMAP)LoadImage(NULL,filename, IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
  if (rPic == 0) return 0;
  int iRet = GetObject(reinterpret_cast<HGDIOBJ>(rPic), sizeof(BITMAP),reinterpret_cast<LPVOID>(&qrBITMAP));
  if (!iRet) rPic=0;
  return 0;
}
