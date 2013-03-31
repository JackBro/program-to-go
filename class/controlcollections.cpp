#include "controlcollections.h"

controlcollections_c::controlcollections_c()
{
  hFont = NULL;
}

controlcollections_c::~controlcollections_c()
{
    //dtor
}

int controlcollections_c::setFont(font_c * aFont) {
  hFont = aFont;
  return 0;
}

initcontrols_c * controlcollections_c::addControl(initcontrols_c * aControl) {
  add((zeiger)aControl);
  if (hFont != NULL) {
    aControl->setFont(hFont->hFont);
  }
  return aControl;
}

int controlcollections_c::setLanguage(language_c * lang) {
  initcontrols_c * control;
  for (int i=0; i<Count; i++) {
    control = (initcontrols_c *)getByIndex(i);
    if (control->langId >= 0) {
      SendMessage(control->Wnd, WM_SETTEXT, 0, (LPARAM)lang->getLang(control->langId));
    }
  }
  return 0;
}