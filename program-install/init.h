#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <windows.h>
#include "../../share/class/initcontrols.h"
#include "../../share/class/systemdefault.h"
#include "../../share/class/file.h"
#include "../../share/class/staticlabel.h"
#include "../../share/class/button.h"
#include "../../share/tools.h"
#include "install.h"

button_c * CButton;

int init(HWND hwnd);

#endif // INIT_H_INCLUDED
