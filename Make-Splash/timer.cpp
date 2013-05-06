#include "timer.h"

int callTimer(HWND hwnd, DWORD timer) {
  if (timer == TIMER_START) {
    KillTimer(hwnd, TIMER_START);
    init2(hwnd);
  } else if (timer == TIMER_STEP1) {
    KillTimer(hwnd, TIMER_STEP1);
    runIt(hwnd,1);
  } else if (timer == TIMER_STEP2) {
    KillTimer(hwnd, TIMER_STEP2);
    runIt(hwnd,2);
  }
  return 0;
}
