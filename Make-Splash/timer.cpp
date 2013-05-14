#include "timer.h"

int callTimer(HWND hwnd, DWORD timer) {
  if (timer == TIMER_STEP1) {
    KillTimer(hwnd, TIMER_STEP1);
    runIt(hwnd,1);
  } else if (timer == TIMER_STEP2) {
    KillTimer(hwnd, TIMER_STEP2);
    runIt(hwnd,2);
  } else if (timer == TIMER_STEP3) {
    KillTimer(hwnd, TIMER_STEP3);
    runIt(hwnd,3);
  } else if (timer == TIMER_STEP4) {
    KillTimer(hwnd, TIMER_STEP4);
    runIt(hwnd,4);
   } else if (timer == TIMER_STEP5) {
    KillTimer(hwnd, TIMER_STEP5);
    runIt(hwnd,5);
   } else if (timer == TIMER_STEP6) {
    KillTimer(hwnd, TIMER_STEP6);
    runIt(hwnd,6);
  }
  return 0;
}
