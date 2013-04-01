#include "fileedit.h"

#include <stdio.h>

fileedit_c::fileedit_c(HWND hWnd, int Icon, int TextLabel, int left, int top, int width, int height):initcontrols_c()
{
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
      ZeroMemory(&ofn, sizeof(ofn));
      ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
      ofn.hwndOwner = hwnd;
      ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
      ofn.lpstrFile = szFileName;
      ofn.nMaxFile = MAX_PATH;
      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT;
      ofn.lpstrDefExt = "txt";
      if(GetOpenFileName(&ofn)) {

//      	SHGetPathFromIDList(pidl, Folder);
//		SendMessage(edit->Wnd,WM_SETTEXT,0,(LPARAM)&Folder);
	  }
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
