/*! \file Make-Splash/LoadSave.h
 *  \brief Routionen zum Speichern und Laden der Daten
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <windows.h>
#include "../share/class/language.h"
#include "../share/class/_comdlg32.h"
#include "../share/class/edit.h"
#include "../share/class/fileedit.h"
#include "../share/class/fileedits.h"

extern edit_c * progname;
extern edit_c * progversion;
extern edit_c * progmessage;
extern fileedit_c * leftpic;
extern fileedit_c * rightpic;
extern fileedits_c * savefile;

int SaveData(HWND wnd, language_c * language);


#endif // LOADSAVE_H
