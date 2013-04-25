#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "resource.h"
#include "init.h"
#include "run.h"


HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
//////////////////////////////////////////////////////////////
  WNDCLASS wnd;
  wnd.style = CS_HREDRAW | CS_VREDRAW; //we will explain this later
  wnd.lpfnWndProc = WndProc;
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hInstance = hInstance;
  wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
  wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
  wnd.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wnd.lpszMenuName = NULL;                     //no menu
  wnd.lpszClassName = TEXT("ProgrammKonfigurator");
  if(!RegisterClass(&wnd)) {
    MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
    return 0;
  }
//////////////////////////////////////////////////////////////
  hInst=hInstance;
//////////////////////////////////////////////////////////////
//  hInstance = hInst;
  MSG msg;
  HWND hwnd;

  RECT rc;
  GetWindowRect(GetDesktopWindow(), &rc);

  hwnd = CreateWindowEx(WS_EX_DLGMODALFRAME ,
                        TEXT("ProgrammKonfigurator"),
                        TEXT("Programm Konfigurator"),
                        WS_VISIBLE | WS_SYSMENU | WS_CAPTION ,
                        (rc.right-400)/2,
                        (rc.bottom-300)/2,
                        400,
                        300,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
  ShowWindow(hwnd, SW_SHOW);              //display the window on the SW_SHOW
//////////////////////////////////////////////////////////////
  init(hwnd);
//////////////////////////////////////////////////////////////
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg){
    case WM_CREATE:{
      SendMessage(hwnd, (UINT)WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(ICON_MAIN)));
      return 0;}
   case WM_INITDIALOG:{
   }
   case WM_DESTROY: {
     setup->checkSave();
     PostQuitMessage(0);
     PostQuitMessage(0);
     return 0;}
   case WM_COMMAND: {
      if (splashfile->event(hwnd, wParam, lParam)) {
        return 0;
      } else if (installpath->event(hwnd, wParam, lParam)) {
        return 0;
      } else if (runfile->event(hwnd, wParam, lParam)) {
        return 0;
      } else if (pages->nextButton->event(hwnd, wParam, lParam)) {
        return 0;
      } else if (pages->prevButton->event(hwnd, wParam, lParam)) {
        return 0;
      } else if ((HWND)lParam == pages->getCloseButtonHwnd()) {
        SendMessage(hwnd,WM_DESTROY,0,0);
      } else if ((DWORD)lParam == (DWORD)langlist->Wnd) {
        if (CBN_SELCHANGE == HIWORD(wParam)) {
          delete language->setCurrentByLabel(langlist->getCurText());
          setup->setLang(language->getCurLang());
          controls->setCurLanguage();
        }
      }
    }
    return TRUE;
    case WM_TIMER:{
    switch (wParam) {
      case TIMER_START: {
        KillTimer(hwnd,TIMER_START);
        installpath->setText(SystemDefault->PrgPath);
        return 0;
      }
      case TIMER_STEP1: {
        KillTimer(hwnd,TIMER_STEP1);
        runIt(hwnd,1);
        return 0;
      }
      case TIMER_STEP2: {
        KillTimer(hwnd,TIMER_STEP2);
        runIt(hwnd,2);
        return 0;
      }
      case TIMER_STEP3: {
        KillTimer(hwnd,TIMER_STEP3);
        runIt(hwnd,3);
        return 0;
      }
      case TIMER_STEP4: {
        KillTimer(hwnd,TIMER_STEP4);
        runIt(hwnd,4);
        return 0;
      }
    }
    }
    return 0;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
