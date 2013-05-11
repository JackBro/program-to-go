/*! \file main_Make-Splash.cpp
 *  \brief Die Hauptdatei vom Projekt "Splash-Screen"
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */

/*! \mainpage Make Splash
 *
 *  Tool zum erstellen einfachen Splashsreens
 */

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "resource.h"
#include "init.h"
#include "timer.h"

HINSTANCE hInst; /**< Halten der Instance vom Programm */

/** \brief Hauptnachrichtenschleife
 *
 * \param hwnd Das Handle des Fensters fuer das die Nachricht bestimmt ist
 * \param msg Die zu bearbeitende Nachricht
 * \param wParam 1. Parameter
 * \param lParam 2. Parameter
 * \return gibt den Bearbeitungsstaus zurueck
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg){
    case WM_CREATE:{
      SendMessage(hwnd, (UINT)WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(ICON_MAIN)));
      return 0;
    }
    case WM_INITDIALOG:{
    }
    case WM_DESTROY: {
      setup->checkSave();
      PostQuitMessage(0);
      return 0;
    }
    case WM_COMMAND: {
      controls->event(hwnd, wParam, lParam);
      return TRUE;
    }
    case WM_TIMER:{
      callTimer(hwnd, wParam);
      return 0;
    }
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}

/** \brief Hauptprocedure von Make-Splash
 *
 * \param hInstance ID der Instance vom Program
 * \param hPrevInstance ID der Instance vom aufrufenden Programm
 * \param lpCmdLine Commandline mit dem das Programm aufgerufenb wird
 * \param iCmdShow Gibt an wie das Programm angezeigt werden soll
 * \return gibt den Fehlerstatus zurueck
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
//////////////////////////////////////////////////////////////
  WNDCLASS wnd;
  wnd.style = CS_HREDRAW | CS_VREDRAW;
  wnd.lpfnWndProc = WndProc;
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hInstance = hInstance;
  wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
  wnd.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wnd.lpszMenuName = NULL;
  wnd.lpszClassName = TEXT("MakeSplash");
  if(!RegisterClass(&wnd)) {
    MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
    return 0;
  }
//////////////////////////////////////////////////////////////
  hInst=hInstance;
//////////////////////////////////////////////////////////////
  MSG msg;
  HWND hwnd;

  RECT rc;
  GetWindowRect(GetDesktopWindow(), &rc);

  hwnd = CreateWindowEx(WS_EX_DLGMODALFRAME ,
                        TEXT("MakeSplash"),
                        TEXT("Make Spalsh"),
                        WS_VISIBLE | WS_SYSMENU | WS_CAPTION ,
                        (rc.right-400)/2,
                        (rc.bottom-300)/2,
                        400,
                        300,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
  ShowWindow(hwnd, SW_SHOW);
//////////////////////////////////////////////////////////////
  init(hwnd);
//////////////////////////////////////////////////////////////
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

