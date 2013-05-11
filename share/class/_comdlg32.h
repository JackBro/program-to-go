/*! \file _comdlg32.h
 *  \brief Die Klassen zum Zugriff auf "commdlg32"
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */

#ifndef _comdlg32_H
#define _comdlg32_H

#include <windows.h>
#include <stdio.h>

/** \class c_getopenfilename
 * Klasse zum Aufrufen des Standarddialoges "GetOpenFileName"
 * \date 2013.05
 */

class c_getopenfilename
{
    public:
      c_getopenfilename();
      virtual ~c_getopenfilename();
      char * get();
      int setFilter(char * aFilter);
      int setPfad(char * aPfad);
      int setHWnd(HWND ahWnd);
    protected:
      HWND hWnd; /**< Speichert das Handle vom Elternfenster */
      char * fname; /**< Speichert den Namen der selktierten Datei */
      char * filter; /**< Speichert die Filtereinstellung */
      char * pfad; /**< Speichert den Standartsuchpfad */
    private:
};

#endif // _comdlg32_H
