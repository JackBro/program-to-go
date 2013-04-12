#include "buttonicon.h"

#include <stdio.h>

buttonicon_c::buttonicon_c(HWND hWnd, int icon, int left, int top, int width, int height)
{
   Wnd = CreateWindow("BUTTON",
                      "",
                      WS_VISIBLE | WS_CHILD |  BS_ICON,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
  HICON hMyIcon=(HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(icon), IMAGE_ICON,
	16, 16, 0);
  SendMessage (Wnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hMyIcon);
  }

buttonicon_c::~buttonicon_c()
{
    //dtor
}
