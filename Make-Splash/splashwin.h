/*! \file Make-Splash/Splashwin.h
 *  \brief Poutinen fuer ein Splashwin zum Erstellen und betrachten des Bildes
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef SPLASHWIN_H_INCLUDED
#define SPLASHWIN_H_INCLUDED

#include <windows.h>

HANDLE createSplash(HINSTANCE hInst, HWND pWnd, char * fName);
int setPrgLabel(char * label);
int setVersiomLabel(char * label);
int setMessageLabel(char * label);
int setLeftPic(char * filename);
int setRightPic(char * filename);
bool savePic(char * filename);
int  closeSplashWin();

#endif // SPLASHWIN_H_INCLUDED
