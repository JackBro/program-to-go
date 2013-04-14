#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <windows.h>
#include "../share/class/initcontrols.h"
#include "../share/class/systemdefault.h"
#include "../share/class/file.h"
#include "../share/class/staticlabel.h"
#include "../share/class/button.h"
#include "../share/tools.h"
#include "../share/class/controlcollections.h"
#include "../share/class/pages.h"
#include "../share/class/unziplib.h"
#include "../share/class/languagebox.h"
#include "../share/class/folderedit.h"
#include "../share/class/editbox.h"
#include "../share/class/radiobutton.h"
#include "../libs/libxml2/tinyxml2.h"
#include "install.h"
#include "resource.h"

button_c * CButton;
extern languagebox_c * langlist;
extern language_c * language;
extern controlcollections_c * controls;
extern pages_c * pages;
extern radiobutton_c * NoAccept;
extern radiobutton_c * Accept;

int init(HWND hwnd);
int init_second(HWND hwnd);

#endif // INIT_H_INCLUDED
