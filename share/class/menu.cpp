#include "menu.h"

#include <stdio.h>

menu_c::menu_c()
{
  m = CreateMenu();
  wnd = 0;
}

menu_c::~menu_c()
{
    //dtor
}

int menu_c::setMenu(HWND awnd) {
  RECT o;
  RECT i1;
  RECT i2;
  wnd = awnd;
  GetWindowRect(wnd, &o);
  GetClientRect(wnd, &i1);
  SetMenu(wnd,m);
  GetClientRect(wnd, &i2);
  SetWindowPos(wnd, 0, 0, 0, o.right-o.left, o.bottom-o.top+i1.bottom-i2.bottom, SWP_NOZORDER | SWP_NOMOVE);
  return 0;
}

int menu_c::Append(int ID, int lang, char * label) {
  MENUITEMINFO mii;
  int * plang = new int[1];
  plang[0] = lang;
  FillMemory(&mii, sizeof (mii), 0);
  mii.cbSize = sizeof (mii);
  mii.fMask = MIIM_STRING | MIIM_FTYPE | MIIM_ID | MIIM_DATA;
  mii.dwTypeData = label;
  mii.fType = MFT_STRING;
  mii.wID = ID;
  mii.dwItemData = (DWORD)plang;
  InsertMenuItem(m, GetMenuItemCount(m), true, &mii);
//  AppendMenu(m, MF_STRING, ID, label);
  return 0;
}

int menu_c::setLanguage( language_c * lang) {
  _setLanguage(m, lang);
  return 0;
}

int menu_c::_setLanguage(HMENU _m, language_c * lang) {
  int iMax = GetMenuItemCount(_m);
  MENUITEMINFO mii;
  FillMemory(&mii, sizeof (mii), 0);
  mii.cbSize = sizeof (mii);
  int * plang;
  for (int i=0; i<iMax; i++ ) {
    mii.fMask = MIIM_DATA;
    if (!GetMenuItemInfo(_m, i, true, &mii)) continue;
    plang = (int*)mii.dwItemData;
    if (plang[0] > -1) {
      mii.dwTypeData = lang->getLang(plang[0]);
      mii.fMask = MIIM_STRING;
      SetMenuItemInfo(_m, i, true, &mii);
    }
    mii.fMask = MIIM_SUBMENU;
    if (!GetMenuItemInfo(_m, i, true, &mii)) continue;
    if (mii.hSubMenu != 0) {
      _setLanguage(mii.hSubMenu,lang);
    }
  }
  if (wnd != 0) DrawMenuBar(wnd);
  return 0;
}

int menu_c::AppendMenu(int ID, int lang, char * label, menu_c * amenu) {
  MENUITEMINFO mii;
  int * plang = new int[1];
  plang[0] = lang;
  FillMemory(&mii, sizeof (mii), 0);
  mii.cbSize = sizeof (mii);
  mii.fMask = MIIM_STRING | MIIM_FTYPE | MIIM_ID | MIIM_DATA | MIIM_SUBMENU;
  mii.dwTypeData = label;
  mii.fType = MFT_STRING;
  mii.wID = ID;
  mii.dwItemData = (DWORD)plang;
  mii.hSubMenu = amenu->getHandle();
  InsertMenuItem(m, GetMenuItemCount(m), true, &mii);
//  AppendMenu(m, MF_STRING, ID, label);
  return 0;
}

HMENU menu_c::getHandle() {
  return m;
}
