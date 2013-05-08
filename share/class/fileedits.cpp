#include "fileedits.h"

#include <stdio.h>

fileedits_c::fileedits_c(HWND hWnd, int Icon, int TextLabel, int left, int top, int width, int height):initcontrols_c()
{
  getdefPfad = NULL;
  edit = new edit_c(hWnd, left, top, width-height, height);
  button = new buttonicon_c(hWnd, Icon,left+width-height, top, height, height);
  aTextLabel = TextLabel;
  parent = hWnd;
}

fileedits_c::~fileedits_c()
{
    //dtor
}

int fileedits_c::show() {
  edit->show();
  button->show();
  return 0;
}

int fileedits_c::hide() {
  edit->hide();
  button->hide();
  return 0;
}

bool fileedits_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  bool ok = ((HWND)lParam == edit->Wnd);
  if (!ok) {
    ok = ((HWND)lParam == button->Wnd);
    if (ok) {
      OPENFILENAME ofn;
      char szFileName[MAX_PATH] = "";
      char * pfad = NULL;
      if (getdefPfad != NULL) {
        pfad = getdefPfad();
      }
      char * filter = lang->getLangText(aTextLabel);
      int len = strlen(filter);
      for (int i=0; i<len; i++) {if (filter[i] == ';'){filter[i]=0;};};
      ZeroMemory(&ofn, sizeof(ofn));
      ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = filter;
      ofn.lpstrFile = szFileName;
      ofn.lpstrInitialDir = pfad;
      ofn.nMaxFile = MAX_PATH;
      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT;
      ofn.lpstrDefExt = "";
      if(GetSaveFileName(&ofn)) {
        edit->setText(szFileName);
	  }
	  delete pfad;
    }
  }
  return ok;
}

int fileedits_c::setFont(HFONT font) {
  SendMessage(edit->Wnd,WM_SETFONT,(WPARAM)font,true);
  return 0;
}

int fileedits_c::setText(char * aText) {
  edit->setText(aText);
  return 0;
}

int fileedits_c::SetGetPfad(cb_getText aProc) {
  getdefPfad = aProc;
  return 0;
}

char * fileedits_c::getText() {
  return edit->getText();
}

int fileedits_c::disable() {
  edit->disable();
  button->disable();
  return 0;
}

int fileedits_c::enable() {
  edit->enable();
  button->enable();
  return 0;
}
