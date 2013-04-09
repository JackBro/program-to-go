#ifndef INIT_H
#define INIT_H


#include "..\..\share\class\systemdefault.h"
#include "..\..\share\class\language.h"
#include "..\..\share\class\controlcollections.h"
#include "..\..\share\class\pages.h"
#include "..\..\share\class\staticlabel.h"
#include "..\..\share\class\folderedit.h"
#include "..\..\share\class\languagebox.h"
#include "..\..\share\class\progress.h"
#include "class/setupfile.h"
#include "resource.h"

#include "run.h"

extern setupfile_c * setup;
extern pages_c * pages;
extern languagebox_c * langlist;
extern controlcollections_c * controls;
extern language_c * language;
extern folderedit_c * sourcepath;
extern folderedit_c * destpath;
extern char * sourcePfad;
extern char * destPfad;
extern char * packName;
extern SystemDefault_c * SystemDefault;

int init(HWND hwnd);
int init_second(HWND hwnd);

#endif // INIT_H
