/*! \file Make-Splash/timer.cpp
 *  \brief Verwaltet die Timerereignisse
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#include "timer.h"

/** \brief Leitealle Timerereignisse den Proceduren zu
 *
 * \param hwnd HWND Handele des Fensters
 * \param timer DWORD Timer-ID
 * \return immer 0
 *
 */
int callTimer(HWND hwnd, DWORD timer) {
  if (timer == TIMER_START) {
    KillTimer(hwnd, TIMER_START);
    init2(hwnd);
  } else  if (timer == TIMER_STEP1) {
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
