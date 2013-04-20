#if run
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#include <windows.h>
#include <stdio.h>
#endif

#include "resource.h"
#include "init.h";
#include "class\layer.h"
#include "..\share\tools.h"

HINSTANCE hInst;
layer_c * layer;
char * TempFolder = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool TimerClose = false;
bool AppClose = false;
int mintime = 5000;

bool hasStarted = false;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
//////////////////////////////////////////////////////////////
  WNDCLASS wnd;
  wnd.style = CS_HREDRAW | CS_VREDRAW;
  wnd.lpfnWndProc = WndProc;
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hInstance = hInstance;
  wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
  wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
  wnd.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wnd.lpszMenuName = NULL;                     //no menu
  wnd.lpszClassName = TEXT("ProgrammStarter");
  if(!RegisterClass(&wnd)) {
    MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
    return 0;
  }
//////////////////////////////////////////////////////////////
//  hInstance = hInst;
  MSG msg;
  HWND hwnd;

  RECT rc;
  GetWindowRect(GetDesktopWindow(), &rc);

  hwnd = CreateWindowEx(WS_EX_DLGMODALFRAME ,
                        TEXT("ProgrammStarter"),
                        TEXT("Programm Starter"),
                        WS_SYSMENU | WS_CAPTION ,
                        (rc.right-400)/2,
                        (rc.bottom-300)/2,
                        400,
                        300,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
  ShowWindow(hwnd, SW_HIDE);              //display the window on the SW_SHOW
//////////////////////////////////////////////////////////////
  hInst=hInstance;
  if (init() == 1) return 1;
//////////////////////////////////////////////////////////////
  SetTimer(hwnd, TIMER_SPLASH_START, 1000, 0);
//////////////////////////////////////////////////////////////
// Prepare Layer if requeste
  bool CanStart = true;
  STARTUPINFO info={sizeof(info)};
  PROCESS_INFORMATION processInfo;
  DWORD dwExitCode;
  DWORD lExitCode;
//////////////////////////////////////////////////////////////
  if ((strlen(runconfig->GetExeLayers()) > 0) &
      ((systemdefault->HiVersion > runconfig->GetHiLayer()) ||
      ((systemdefault->HiVersion == runconfig->GetHiLayer()) & (systemdefault->LoVersion > runconfig->GetLoLayer())))) {
    if (systemdefault->DriveRemovable()) {
      TempFolder = new char[MAX_PATH];
      GetTempFolderName(systemdefault->TempPath,"PS",0,TempFolder);
//      GetTempFolderName("\\","PS",0,TempFolder);
      if (CopyFolder(appdir,TempFolder,hwnd) == 1) {CanStart = false; printf("error");};
// Ändern des Exefiles in das Tempdir
      delete exefile;
      exefile = new char[MAX_PATH];
      memcpy(exefile,TempFolder,strlen(TempFolder)+1);
      memcpy(exefile+strlen(exefile),runconfig->ExeFile,strlen(runconfig->ExeFile)+1);
      for (int i =0; i< strlen(exefile); i++) {if (exefile[i] == '/') {exefile[i] = '\\';}}
    }
    layer = new layer_c(exefile,runconfig->GetExeLayers());
  }
//////////////////////////////////////////////////////////////
  while (true) {
  //-- see if the task has terminated
    if (!hasStarted) {
      hasStarted = true;
      if (!FileExists(exefile)) {CanStart = false;}
      if (CanStart) {
        CreateProcess( exefile, NULL, NULL, NULL, TRUE, 0, NULL, appdir, &info, &processInfo);
      }
      SetTimer(hwnd,TIMER_MIN,mintime, NULL);
    }
    if (CanStart) {
      dwExitCode = WaitForSingleObject(processInfo.hProcess, 0);
    } else {
      dwExitCode = WAIT_FAILED;
    }
    if (((dwExitCode == WAIT_FAILED   ) || (dwExitCode == WAIT_OBJECT_0 ) || (dwExitCode == WAIT_ABANDONED)) && CanStart ) {
      //-- get the process exit code
      if (!CanStart) {
        GetExitCodeProcess(processInfo.hProcess, &dwExitCode);
      //-- the task has ended so close the handle
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);

      //-- save the exit code
//////////////////////////////////////////////////////////////
// Remove Layer if requested
        if ((strlen(runconfig->GetExeLayers()) > 0) &
          ((systemdefault->HiVersion > runconfig->GetHiLayer()) ||
          ((systemdefault->HiVersion == runconfig->GetHiLayer()) & (systemdefault->LoVersion > runconfig->GetLoLayer())))) {
          if (systemdefault->DriveRemovable()) {
//      printf("I Need to Move\n");
            DeleteFolder(TempFolder);
          }
          delete layer;
        }
      }
//////////////////////////////////////////////////////////////
      lExitCode = dwExitCode;
 //     SendMessage(hwnd,WM_CLOSE,0,0);
    } else {
      if (!CanStart) SendMessage(hwnd,WM_CLOSE,0,0);
    //-- see if there are any message that need to be processed
      while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {
        if (msg.message == WM_QUIT) {
          return 0;
        }
         //-- process the message queue
        if (GetMessage(&msg, 0, 0, 0)) {
        //-- process the message
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      }
    }
  }
  return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_INITDIALOG:
    {
    }
    case WM_DESTROY:
      if (TempFolder != NULL) {DeleteFolder(TempFolder);}
      PostQuitMessage(0);
      return 0;
    case WM_CLOSE : {
      if (TimerClose) {
        SendMessage(hwnd, WM_DESTROY, 0,0);
      } else {
        AppClose = true;
      }
      return 0;
    }
    case WM_TIMER : {
      if (wParam == TIMER_MIN) {
        KillTimer(hwnd,TIMER_MIN);
        if (AppClose) {
          SendMessage(hwnd, WM_DESTROY, 0,0);
        } else {
          TimerClose = true;
        }
      }
      if (wParam == TIMER_SPLASH_START) {
        KillTimer(hwnd,TIMER_SPLASH_START);
        printf("Splash Start\n");
      }
      return 0;
    }

    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        }
    }
    return TRUE;
    }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
