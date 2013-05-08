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
#include "../share/class/progress.h"
#include "../share/class/edit.h"
#include "../share/class/fileedit.h"
#include "../share/class/fileedits.h"
#include "class/setupfile.h"
#include "resource.h"
#include "run.h"

extern controlcollections_c * controls;
extern setupfile_c * setup;
extern staticlabel_c * progresslabel;
extern edit_c * progname;
extern edit_c * progversion;
extern edit_c * progmessage;
extern progress_c * progressbar;
extern fileedit_c * leftpic;
extern fileedit_c * rightpic;
extern SystemDefault_c * SystemDefault;
extern fileedits_c * savefile;

int init(HWND wnd);
int init2(HWND wnd);

#endif // INIT_H
