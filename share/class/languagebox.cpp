#include "languagebox.h"

#include <stdio.h>

languagebox_c::languagebox_c(HWND hWnd, int left, int top, int width, int height):dropdownlist_c(hWnd, true, left,top,width,height)
{

}

languagebox_c::~languagebox_c()
{
    //dtor
}

int languagebox_c::setLangList() {
  if (lang != NULL) {
    for (int i=0; i<lang->Count; i++) {
      addEntry(lang->getLangName(i));
    }
    if (lang->current >= 0) {selectByText(lang->getLangName(lang->current));}
  }
  return 0;
}

int languagebox_c::selectByText(char * text) {
  int id = SendMessage(Wnd,CB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)text);
  SendMessage(Wnd,CB_SETCURSEL,id,0);
  return 0;
}

char * languagebox_c::getCurText() {
  int i = getCurSel();
  int size = SendMessage(Wnd,CB_GETLBTEXTLEN,i,0)+1;
  char * text = new char[size];
  SendMessage(Wnd,CB_GETLBTEXT,i,(LPARAM)text);
  return text;
}

bool languagebox_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  if (Wnd == (HWND)lParam) {
    if (onClick != NULL) {onClick(); }
  }
  return false;
}

