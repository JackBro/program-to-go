#ifndef RUN_H
#define RUN_H

#include <windows.h>
#include "splashwin.h"
#include "resource.h"

#include "../share/class/staticlabel.h"
#include "../share/class/edit.h"
#include "../share/class/progress.h"

extern staticlabel_c * progresslabel;
extern edit_c * progname;
extern progress_c * progressbar;

int runIt(HWND wnd ,int step);

#endif // RUN_H
