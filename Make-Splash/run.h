#ifndef RUN_H
#define RUN_H

#include <windows.h>
#include "splashwin.h"

#include "../share/class/staticlabel.h"

extern staticlabel_c * progresslabel;

int runIt(HWND wnd ,int step);

#endif // RUN_H
