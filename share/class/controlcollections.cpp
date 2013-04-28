#include "controlcollections.h"

#include <stdio.h>

controlcollections_c::controlcollections_c()
{
  hFont = NULL;
  hLang = NULL;
}

controlcollections_c::~controlcollections_c()
{
    //dtor
}

int controlcollections_c::setFont(font_c * aFont) {
  hFont = aFont;
  return 0;
}

int controlcollections_c::setLanguage(language_c * aLang) {
  hLang = aLang;
  return 0;
}

initcontrols_c * controlcollections_c::addControl(initcontrols_c * aControl) {
  add((zeiger)aControl);
  if (hFont != NULL) {
    aControl->setFont(hFont->hFont);
  }
  if (hLang !=  NULL) {
    aControl->setLanguage(hLang);
  }
  return aControl;
}

int controlcollections_c::setCurLanguage() {
  initcontrols_c * control;
  for (int i=0; i<Count; i++) {
    control = (initcontrols_c *)getByIndex(i);
    control->setCurLang();
  }
  return 0;
}

int controlcollections_c::event(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  initcontrols_c * c;
  for (int i=0; i<Count; i++) {
    c = (initcontrols_c*)getByIndex(i);
    c->event(hwnd, wParam, lParam);
  }
  return 0;
}
