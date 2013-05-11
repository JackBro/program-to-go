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
      c_getsavefilename * ofn = new c_getsavefilename;
      ofn->setHWnd(hwnd);
      ofn->setFilter(lang->getLangText(aTextLabel));
      if (getdefPfad != NULL) {
        ofn->setPfad(getdefPfad());
      }
      edit->setText(ofn->get());
      delete ofn;
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
