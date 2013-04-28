#ifndef INIT_H
#define INIT_H

#include <windows.h>

#include "../share/class/systemdefault.h"
#include "../share/class/language.h"
#include "../share/class/controlcollections.h"
#include "../share/class/font.h"
#include "../share/class/pages.h"
#include "../share/class/staticlabel.h"
#include "../share/class/languagebox.h"
#include "class/setupfile.h"

extern controlcollections_c * controls;

int init(HWND wnd);

#endif // INIT_H
