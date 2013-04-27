#ifndef INIT_H
#define INIT_H

#include "..\share\class\systemdefault.h"
#include "..\share\class\language.h"
#include "..\share\class\controlcollections.h"
#include "..\share\class\pages.h"
#include "..\share\class\staticlabel.h"
#include "..\share\class\buttonIcon.h"
#include "..\share\class\folderedit.h"
#include "..\share\class\fileedit.h"
#include "..\share\class\numedit.h"
#include "..\share\class\languagebox.h"
#include "..\share\class\dropdownlist.h"
#include "..\share\class\progress.h"
#include "..\share\class\menu.h"
#include "class/setupfile.h"
#include "resource.h"

#include "run.h"

extern font_c * font;
extern setupfile_c * setup;
extern pages_c * pages;
extern languagebox_c * langlist;
extern controlcollections_c * controls;
extern language_c * language;
extern folderedit_c * installpath;
extern SystemDefault_c * SystemDefault;
extern fileedit_c * runfile;
extern fileedit_c * splashfile;
extern progress_c * progressbar;
extern staticlabel_c * progresslabel;
extern char * prgPfad;
extern char * prgExefile;
extern int layer;
extern numedit_c * delay;
extern numedit_c * hold;


int init(HWND hwnd);

#endif // INIT_H
