#include "radiobutton.h"

#include <stdio.h>

radiobutton_c::radiobutton_c(HWND hWnd, char * text, int lang, int left, int top, int width, int height)
{
   Wnd = CreateWindow("BUTTON",
                      text,
                      WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
  langId = lang;
  onClick = NULL;
}

radiobutton_c::~radiobutton_c()
{
    //dtor
}

bool radiobutton_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  if (Wnd == (HWND)lParam) {
    if (onClick != NULL) {onClick();}
  }
  return false;
}

bool radiobutton_c::isChecked() {
  return BST_CHECKED == SendMessage(Wnd,BM_GETCHECK,0,0);
}

int radiobutton_c::check(bool state) {
  if (state) {
    SendMessage(Wnd, BM_SETCHECK, BST_CHECKED, 0);
  } else {
    SendMessage(Wnd, BM_SETCHECK, BST_UNCHECKED, 0);
  }
  return 0;
}

