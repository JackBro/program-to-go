/*! \file Make-Splash/run.h
 *  \brief Routinen zum erstellen des Splash-bildes
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */

#ifndef RUN_H
#define RUN_H

#include <windows.h>
#include "splashwin.h"
#include "resource.h"

#include "../share/class/staticlabel.h"
#include "../share/class/edit.h"
#include "../share/class/fileedit.h"
#include "../share/class/fileedits.h"
#include "../share/class/progress.h"
#include "../share/class/systemdefault.h"
#include "../share/class/pages.h"

extern staticlabel_c * progresslabel;
extern edit_c * progname;
extern edit_c * progversion;
extern progress_c * progressbar;
extern edit_c * progmessage;
extern fileedit_c * leftpic;
extern SystemDefault_c * SystemDefault;
extern fileedit_c * rightpic;
extern fileedits_c * savefile;
extern pages_c * pages;

int runIt(HWND wnd ,int step);

#endif // RUN_H
