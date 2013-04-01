#include "dropdownlist.h"

#if run
#include <stdio.h>
#endif

dropdownlist_c::dropdownlist_c(HWND hWnd, int left, int top, int width, int height)
{
   Wnd = CreateWindow("COMBOBOX",
                      NULL,WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | CBS_SORT | WS_TABSTOP,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);
}

dropdownlist_c::~dropdownlist_c()
{
    //dtor
}

int dropdownlist_c::setLangList() {
  if (lang != NULL) {
    for (int i=0; i<lang->Count; i++) {
      addEntry(lang->getLangName(i));
    }
  }
  selectByText(lang->getLangName(lang->current));
  return 0;
}

int dropdownlist_c::addEntry(char * text) {
  SendMessage(Wnd,CB_ADDSTRING,0, (LPARAM)text);
  return 0;
}

int dropdownlist_c::selectByText(const char * text) {
  SendMessage(Wnd,CB_SETCURSEL,SendMessage(Wnd,CB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)text),0);
  return 0;
}

int dropdownlist_c::getCurSel() {
  return SendMessage(Wnd,CB_GETCURSEL,0,0);
}

char * dropdownlist_c::getCurText() {
  int i = getCurSel();
  int size = SendMessage(Wnd,CB_GETLBTEXTLEN,i,0)+1;
  char * text = new char[size];
  SendMessage(Wnd,CB_GETLBTEXT,i,(LPARAM)text);
  return text;
}
