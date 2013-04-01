#ifndef INIT_H
#define INIT_H

#include "..\share\class\systemdefault.h"
#include "..\share\class\language.h"
#include "..\share\class\controlcollections.h"
#include "..\share\class\pages.h"
#include "..\share\class\staticlabel.h"
#include "..\share\class\buttonIcon.h"
#include "..\share\class\folderedit.h"
#include "..\share\class\dropdownlist.h"
#include "class/setupfile.h"
#include "resource.h"

extern font_c * font;
extern setupfile_c * setup;
extern pages_c * pages;
extern dropdownlist_c * langlist;
extern controlcollections_c * controls;
extern language_c * language;
extern folderedit_c * installpath;
extern SystemDefault_c * SystemDefault;

int init(HWND hwnd);

#endif // INIT_H
