/*! \file Make-Splash/timer.h
 *  \brief Verwaltet die Timerereignisse
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>
#include "resource.h"
#include "init.h"
#include "run.h"

int callTimer(HWND hwnd, DWORD timer);

#endif // TIMER_H
