#include "button.h"

#include <stdio.h>

button_c::button_c(HWND hWnd, const char * text, int lang, int left, int top, int width, int height)
{
   Wnd = CreateWindow("BUTTON",
                      text,
                      WS_VISIBLE | WS_CHILD,
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

button_c::~button_c()
{
    //dtor
}

bool button_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  if (Wnd == (HWND)lParam) {
    if (onClick != NULL) {onClick();}
  }
  return false;
}
