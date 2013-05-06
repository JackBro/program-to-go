#include "run.h"

HANDLE splash;

int runIt(HWND wnd ,int step) {
  if (step == 0) {
    progressbar->setRange(0,2);
    progresslabel->setLangId(5);
    splash = createSplash(GetModuleHandle (0), wnd, "config/splash.bmp");
    ShowWindow((HWND)splash, SW_SHOW);
    progressbar->setValue(1);
    SetTimer(wnd, TIMER_STEP1, 100, NULL);
  } else if (step == 1) {
    progresslabel->setLangId(7);
    setPrgLabel(progname->getText());
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    SetTimer(wnd, TIMER_STEP2, 100, NULL);
  } else if (step == 2) {
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

//    MessageBox(0,"Call Run","",0);
  }
  return 0;
}
