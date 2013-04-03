#include "fileedit.h"

#include <stdio.h>

fileedit_c::fileedit_c(HWND hWnd, int Icon, int TextLabel, int left, int top, int width, int height):initcontrols_c()
{
  getdefPfad = NULL;
  edit = new edit_c(hWnd, left, top, width-height, height);
  button = new buttonicon_c(hWnd, Icon,left+width-height, top, height, height);
  aTextLabel = TextLabel;
  parent = hWnd;
}

fileedit_c::~fileedit_c()
{
    //dtor
}

int fileedit_c::show() {
  edit->show();
  button->show();
  return 0;
}

int fileedit_c::hide() {
  edit->hide();
  button->hide();
  return 0;
}

bool fileedit_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
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
      ofn.lpstrDefExt = "txt";
      if(GetOpenFileName(&ofn)) {
        edit->setText(szFileName);
	  }
	  delete pfad;
    }
  }
  return ok;
}

int fileedit_c::setFont(HFONT font) {
  SendMessage(edit->Wnd,WM_SETFONT,(WPARAM)font,true);
  return 0;
}

int fileedit_c::setText(char * aText) {
  edit->setText(aText);
  return 0;
}

int fileedit_c::SetGetPfad(cb_getText aProc) {
  getdefPfad = aProc;
  return 0;
}
