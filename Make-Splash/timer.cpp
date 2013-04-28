#include "timer.h"

int callTimer(HWND hwnd, DWORD timer) {
  if (timer == TIMER_START) {
    KillTimer(hwnd, TIMER_START);
    init2(hwnd);
  }
  return 0;
}
