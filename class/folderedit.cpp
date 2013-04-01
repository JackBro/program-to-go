#include "folderedit.h"

#include <stdio.h>

folderedit_c::folderedit_c(HWND hWnd, int Icon, int left, int top, int width, int height):initcontrols_c()
{
  edit = new edit_c(hWnd, left, top, width-height, height);
  button = new buttonicon_c(hWnd, Icon,left+width-height, top, height, height);
}

folderedit_c::~folderedit_c()
{
    //dtor
}

int folderedit_c::show() {
  edit->show();
  button->show();
  return 0;
}

int folderedit_c::hide() {
  edit->hide();
  button->hide();
  return 0;
}
