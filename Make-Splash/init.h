/*! \file Make-Splash/init.h
 *  \brief Initialiesiert das Hauptfenster
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef INIT_H
#define INIT_H

#include <windows.h>

#include "../share/class/systemdefault.h"
#include "../share/class/language.h"
#include "../share/class/controlcollections.h"
#include "../share/class/font.h"
#include "../share/class/pages.h"
#include "../share/class/staticlabel.h"
#include "../share/class/languagebox.h"
#include "../share/class/progress.h"
#include "../share/class/edit.h"
#include "../share/class/fileedit.h"
#include "../share/class/fileedits.h"
#include "../share/class/menu.h"
#include "class/setupfile.h"
#include "resource.h"
#include "run.h"

extern controlcollections_c * controls; /**< Speichert alle Visuellen Elemente */
extern setupfile_c * setup; /**< Speichert die Grundeinstellungen */
extern staticlabel_c * progresslabel; /**< Speichert das Label fuer die Anzeige des Fortschritts */
extern edit_c * progname; /**< Speichert das Element fuer die Eingabe des Namens */
extern edit_c * progversion;  /**< Speichert das Element fuer die Eingabe der Version */
extern edit_c * progmessage;  /**< Speichert das Element fuer die Eingabe des Kommentares */
extern progress_c * progressbar;  /**< Speichert das den Zugriff auf die Progressbar */
extern fileedit_c * leftpic;  /**< Speichert den Ort der Datei des linken Bildes */
extern fileedit_c * rightpic; /**< Speichert den Ort der Datei des rechten Bildes */
extern SystemDefault_c * SystemDefault; /**< Speichert die Startinformationen des Programms */
extern fileedits_c * savefile; /**< Speichert das Element wo das Bild gespeichert werden soll */
extern pages_c * pages; /**< Speichert die Seitenverwaltung des Dialoges */

int init(HWND wnd);

#endif // INIT_H
