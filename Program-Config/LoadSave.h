#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <windows.h>
#include "../share/class/language.h"
#include "../share/class/folderedit.h"
#include "../share/class/fileedit.h"
#include "../share/class/dropdownlist.h"
#include "../share/class/numedit.h"
#include "../libs/libxml2/tinyxml2.h"

extern folderedit_c * installpath;
extern fileedit_c * runfile;
extern dropdownlist_c * version;
extern fileedit_c * splashfile;
extern numedit_c * delay;
extern numedit_c * hold;

int SaveData(HWND hwnd, language_c * lang);
int SaveAsData(HWND hwnd, language_c * lang);

#endif // LOADSAVE_H
