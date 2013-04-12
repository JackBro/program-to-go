#include "dropdownlist.h"

dropdownlist_c::dropdownlist_c(HWND hWnd, bool sort, int left, int top, int width, int height)
{
   DWORD Style = WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_HASSTRINGS | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_TABSTOP;
   if (sort) {
     Style = Style | CBS_SORT;
   }
   Wnd = CreateWindow("COMBOBOX",
                      NULL, Style,
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

int dropdownlist_c::addEntry(char * text) {
  SendMessage(Wnd,CB_ADDSTRING,0, (LPARAM)text);
  return 0;
}

int dropdownlist_c::getCurSel() {
  return SendMessage(Wnd,CB_GETCURSEL,0,0);
}

