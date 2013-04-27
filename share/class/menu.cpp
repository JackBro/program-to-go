#include "menu.h"

#include <stdio.h>

menu_c::menu_c()
{
  m = CreateMenu();
}

menu_c::~menu_c()
{
    //dtor
}

int menu_c::setMenu(HWND wnd) {
  RECT o;
  RECT i1;
  RECT i2;
  GetWindowRect(wnd, &o);
  GetClientRect(wnd, &i1);
  SetMenu(wnd,m);
  GetClientRect(wnd, &i2);
//  printf("%d %d\n", o.left, o.right);
  SetWindowPos(wnd, 0, 0, 0, o.right-o.left, o.bottom-o.top+i1.bottom-i2.bottom, SWP_NOZORDER | SWP_NOMOVE);
  return 0;
}

int menu_c::Append(int ID, char * label) {
  AppendMenu(m, MF_STRING, ID, label);
  return 0;
}
