#include "run.h"

HANDLE splash;
char splashbmp[] = "config/splash.bmp";

int runIt(HWND wnd ,int step) {
  if (step == 0) {
    progressbar->setRange(0,7);
    progresslabel->setLangId(5);
    char * temp = new char[MAX_PATH];
    memcpy(temp, SystemDefault->PrgPath, strlen(SystemDefault->PrgPath)+1);
    memcpy(temp+strlen(temp), splashbmp, strlen(splashbmp)+1);
    splash = createSplash(GetModuleHandle (0), wnd, temp);
    delete[] temp;
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
    progresslabel->setLangId(14);
    setLeftPic(leftpic->getText());
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    progressbar->setValue(5);
    SetTimer(wnd, TIMER_STEP5, 100, NULL);
  } else if (step == 5) {
    progresslabel->setLangId(15);
    setRightPic(rightpic->getText());
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    progressbar->setValue(6);
    SetTimer(wnd, TIMER_STEP6, 100, NULL);
  } else if (step == 6) {
    RedrawWindow((HWND)splash, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

//    MessageBox(0,"Call Run","",0);
  }
  return 0;
}
