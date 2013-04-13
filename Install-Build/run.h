#ifndef RUN_H
#define RUN_H

#include "..\share\class\pages.h"
#include "..\share\class\progress.h"
#include "..\share\class\file.h"
#include "..\share\class\staticlabel.h"
#include "..\share\class\checkbox.h"
#include "..\share\tools.h"
#include "class\ziplib.h"
#include "resource.h"
#include "install.h"

extern pages_c * pages;
extern progress_c * progressbar;
extern staticlabel_c * progresslabel;
extern char * sourcePfad;
extern char * destPfad;
extern char * packName;
extern char * lizensFile;
extern checkbox_c * lizensbox;

int runIt(HWND wnd, int step);

#endif // RUN_H
