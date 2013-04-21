#ifndef RUN_H
#define RUN_H

#include "..\share\class\pages.h"
#include "..\share\class\progress.h"
#include "..\share\class\staticlabel.h"
#include "..\share\class\xmlfile.h"
#include "..\share\tools.h"
#include "resource.h"
#include "icon.h"

extern pages_c * pages;
extern progress_c * progressbar;
extern staticlabel_c * progresslabel;
extern char * prgPfad;
extern char * prgExefile;
extern int layer;

int runIt(HWND wnd, int step);

#endif // RUN_H
