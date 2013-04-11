#ifndef RUN_H
#define RUN_H

#include "..\..\share\class\pages.h"
#include "..\..\share\class\progress.h"
#include "..\..\share\class\file.h"
#include "..\..\share\class\staticlabel.h"
#include "..\..\share\tools.h"
#include "class\ziplib.h"
#include "resource.h"

extern pages_c * pages;
extern progress_c * progressbar;
extern staticlabel_c * progresslabel;
extern char * sourcePfad;
extern char * destPfad;
extern char * packName;

int runIt(HWND wnd, int step);

#endif // RUN_H
