#include "run.h"

HANDLE splash;

int runIt(HWND wnd ,int step) {
  if (step == 0) {
    progressbar->setRange(0,5);
    progresslabel->setLangId(5);
    splash = createSplash(GetModuleHandle (0), wnd, "config/splash.bmp");
    ShowWindow((HWND)splash, SW_SHOW);
    progressbar->setValue(1);
    SetTimer(wnd, TIMER_STEP1, 100, NULL);
  } else if (step == 1) {
    progresslabel->setLangId(7);
    setPrgLabel(progname->getText());
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    progressbar->setValue(2);
    SetTimer(wnd, TIMER_STEP2, 100, NULL);
  } else if (step == 2) {
    progresslabel->setLangId(8);
    setVersiomLabel(progversion->getText());
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    progressbar->setValue(3);
    SetTimer(wnd, TIMER_STEP3, 100, NULL);
  } else if (step == 3) {
    progresslabel->setLangId(11);
    setMessageLabel(progmessage->getText());
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    progressbar->setValue(4);
    SetTimer(wnd, TIMER_STEP4, 100, NULL);
  } else if (step == 4) {
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

//    MessageBox(0,"Call Run","",0);
  }
  return 0;
}
