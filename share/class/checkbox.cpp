#include "checkbox.h"

#include <stdio.h>

checkbox_c::checkbox_c(HWND hWnd, int left, int top, int width, int height)
{
   Wnd = CreateWindow("BUTTON",
                      "",
                      WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_AUTOCHECKBOX,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
  langId = -1;
  onClick = NULL;
}

checkbox_c::~checkbox_c()
{
    //dtor
}

bool checkbox_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  if (Wnd == (HWND)lParam) {
    if (onClick != NULL) {onClick();}
  }
  return false;
}

bool checkbox_c::isChecked() {
  return BST_CHECKED == SendMessage(Wnd,BM_GETCHECK,0,0);
}

