#include "run.h"

int runIt(HWND wnd ,int step) {
  if (step == 0) {
    progresslabel->setLangId(5);
    HANDLE splash = createSplash(GetModuleHandle (0), wnd, "config/splash.bmp");
    ShowWindow((HWND)splash, SW_SHOW);
//    MessageBox(0,"Call Run","",0);
  }
  return 0;
}
