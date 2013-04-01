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

bool folderedit_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  bool ok = ((HWND)lParam == edit->Wnd);
  if (!ok) {
    ok = ((HWND)lParam == button->Wnd);
    if (ok) {
      BROWSEINFO   bi       = { 0 };
      LPITEMIDLIST pidl     = NULL;
      char Folder[MAX_PATH];
      char szFolder[MAX_PATH];
      char text[] = "Dies ist eine Nachricht";
      bi.hwndOwner      = Wnd;
      bi.pszDisplayName = Folder;
	  bi.pidlRoot       = NULL;  //StartFolder
	  bi.lpszTitle      = text;
      bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
      if ((pidl = SHBrowseForFolder(&bi)) != NULL) {
		SHGetPathFromIDList(pidl, Folder);
		SendMessage(edit->Wnd,WM_SETTEXT,0,(LPARAM)&Folder);
	  }
    }
  }
  return ok;
}

int folderedit_c::setFont(HFONT font) {
  SendMessage(edit->Wnd,WM_SETFONT,(WPARAM)font,true);
  return 0;
}
