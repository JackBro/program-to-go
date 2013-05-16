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
HWND mywnd;

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
  RegisterClass(&wnd);
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
  mywnd = hwnd;

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

bool savePic(char * fname)
{
  bool ret = false;
  // get screen rectangle
  RECT windowRect;
  GetWindowRect(mywnd, &windowRect);
  // bitmap dimensions
  int bitmap_dx = windowRect.right - windowRect.left;
  int bitmap_dy = windowRect.bottom - windowRect.top;
  // create file
  HANDLE f = CreateFile(fname,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
  if (f == 0) return ret;

  // save bitmap file headers
  BITMAPFILEHEADER fileHeader;
  BITMAPINFOHEADER infoHeader;

  fileHeader.bfType      = 0x4d42;
  fileHeader.bfSize      = 0;
  fileHeader.bfReserved1 = 0;
  fileHeader.bfReserved2 = 0;
  fileHeader.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  infoHeader.biSize          = sizeof(infoHeader);
  infoHeader.biWidth         = bitmap_dx;
  infoHeader.biHeight        = bitmap_dy;
  infoHeader.biPlanes        = 1;
  infoHeader.biBitCount      = 24;
  infoHeader.biCompression   = BI_RGB;
  infoHeader.biSizeImage     = 0;
  infoHeader.biXPelsPerMeter = 0;
  infoHeader.biYPelsPerMeter = 0;
  infoHeader.biClrUsed       = 0;
  infoHeader.biClrImportant  = 0;

  DWORD fwrite;
  WriteFile(f,&fileHeader,sizeof(BITMAPFILEHEADER),&fwrite,NULL);
  if (sizeof(BITMAPFILEHEADER) != fwrite) return ret;

  WriteFile(f,&infoHeader,sizeof(BITMAPINFOHEADER),&fwrite,NULL);
  if (sizeof(BITMAPINFOHEADER) != fwrite) return ret;


  // dibsection information
  BITMAPINFO info;
  info.bmiHeader = infoHeader;

  // ------------------
  // THE IMPORTANT CODE
  // ------------------
  // create a dibsection and blit the window contents to the bitmap
  HDC winDC = GetWindowDC(mywnd);
  HDC memDC = CreateCompatibleDC(winDC);
  BYTE* memory = 0;
  HBITMAP bitmap = CreateDIBSection(winDC, &info, DIB_RGB_COLORS, (void**)&memory, 0, 0);
  SelectObject(memDC, bitmap);
  BitBlt(memDC, 0, 0, bitmap_dx, bitmap_dy, winDC, 0, 0, SRCCOPY);
  DeleteDC(memDC);
  ReleaseDC(mywnd, winDC);

  // save dibsection data
  int bytes = (((24*bitmap_dx + 31) & (~31))/8)*bitmap_dy;
  WriteFile(f,memory,bytes,&fwrite,NULL);
  DeleteObject(bitmap);
  CloseHandle(f);
  ret = true;
  return ret;
}

int  closeSplashWin() {
  SendMessage(mywnd,WM_CLOSE,0,0);
  return 0;
}
