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
#include "resource.h"

extern controlcollections_c * controls;
extern setupfile_c * setup;

int init(HWND wnd);
int init2(HWND wnd);

#endif // INIT_H
