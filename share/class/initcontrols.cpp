#include "initcontrols.h"

#include <stdio.h>

bool ControlsInited = false;

initcontrols_c::initcontrols_c() {
  if (! ControlsInited) {
    ControlsInited = true;
    INITCOMMONCONTROLSEX iccx;
    iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
    iccx.dwICC= ICC_STANDARD_CLASSES | ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&iccx);
  }
  langId = -1;
  lang = NULL;
}

initcontrols_c::~initcontrols_c() {
    //dtor
}

int initcontrols_c::setFont(HFONT font) {
  SendMessage(Wnd,WM_SETFONT,(WPARAM)font,true);
  return 0;
}

int initcontrols_c::enable() {
  EnableWindow(Wnd,true);
  return 0;
}

int initcontrols_c::disable() {
  EnableWindow(Wnd,false);
  return 0;
}

int initcontrols_c::hide()
{
  ShowWindow(Wnd,SW_HIDE);
  return 0;
}

int initcontrols_c::show()
{
  ShowWindow(Wnd,SW_SHOW);
  return 0;
}

int initcontrols_c::setText(char * aText) {
  SendMessage(Wnd,WM_SETTEXT,0,(LPARAM)aText);
  return 0;
}

char * initcontrols_c::getText() {
  int size = SendMessage(Wnd,WM_GETTEXTLENGTH,0,0);
  char * text = new char[size+1];
  SendMessage(Wnd,WM_GETTEXT,size+1,(LPARAM)text);
  return text;
}

bool initcontrols_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  return false;
}

int initcontrols_c::setLanguage(language_c * aLang) {
  lang = aLang;
  return 0;
}

int initcontrols_c::setCurLang() {
  if (langId >= 0) {
    char * aText = lang->getLangText(langId);
//    languagefile_c * file = (languagefile_c*)lang->getByIndex(current);
    SendMessage(Wnd,WM_SETTEXT,0,(LPARAM)aText);
  }
  return 0;
}

int initcontrols_c::setLangId(int id) {
  langId = id;
  setCurLang();
  return 0;
}
