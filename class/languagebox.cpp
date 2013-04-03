#include "languagebox.h"

#if run
#include <stdio.h>
#endif

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
  }
  selectByText(lang->getLangName(lang->current));
  return 0;
}

int languagebox_c::selectByText(const char * text) {
  SendMessage(Wnd,CB_SETCURSEL,SendMessage(Wnd,CB_FINDSTRINGEXACT,(WPARAM)-1,(LPARAM)text),0);
  return 0;
}

char * languagebox_c::getCurText() {
  int i = getCurSel();
  int size = SendMessage(Wnd,CB_GETLBTEXTLEN,i,0)+1;
  char * text = new char[size];
  SendMessage(Wnd,CB_GETLBTEXT,i,(LPARAM)text);
  return text;
}
