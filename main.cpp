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
char TempFolder[MAX_PATH];

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
  hInst=hInstance;
  init();
//////////////////////////////////////////////////////////////
// Prepare Layer if requeste
  bool CanStart = true;
  if ((strlen(runconfig->ExeLayers) > 0) &
      ((systemdefault->HiVersion > runconfig->HiLayer) ||
      ((systemdefault->HiVersion == runconfig->HiLayer) & (systemdefault->LoVersion > runconfig->LoLayer)))) {
    if (systemdefault->DriveRemovable()) {
//      printf("I Need to Move\n");
      GetTempFolderName(systemdefault->TempPath,"PS",0,TempFolder);
      if (CopyFolder(appdir,TempFolder,hwnd) == 1) {CanStart = false;};
// Ändern des Exefiles in das Tempdir
      delete exefile;
      exefile = new char[strlen(TempFolder)+strlen(runconfig->ExeFile)+2];
      sprintf(exefile,"%s%s\0",TempFolder,runconfig->ExeFile);
      exefile[strlen(TempFolder)+strlen(runconfig->ExeFile)] = 0;
      for (int i =0; i< strlen(exefile); i++) {if (exefile[i] == '/') {exefile[i] = '\\';}}
      printf("%s\n",exefile);
    }
    layer = new layer_c(exefile,runconfig->ExeLayers);
  }
//////////////////////////////////////////////////////////////
    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION processInfo;
  if (CanStart) {
    CreateProcess( exefile, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
  }
    DWORD lExitCode;
  while (true) {
  //-- see if the task has terminated
    DWORD dwExitCode = WaitForSingleObject(processInfo.hProcess, 0);
    if (   (dwExitCode == WAIT_FAILED   ) || (dwExitCode == WAIT_OBJECT_0 ) || (dwExitCode == WAIT_ABANDONED) ) {
      DWORD dwExitCode;
      //-- get the process exit code
      GetExitCodeProcess(processInfo.hProcess, &dwExitCode);
      //-- the task has ended so close the handle
      CloseHandle(processInfo.hThread);
      CloseHandle(processInfo.hProcess);
      //-- save the exit code
//////////////////////////////////////////////////////////////
// Remove Layer if requested
  if ((strlen(runconfig->ExeLayers) > 0) &
      ((systemdefault->HiVersion > runconfig->HiLayer) ||
      ((systemdefault->HiVersion == runconfig->HiLayer) & (systemdefault->LoVersion > runconfig->LoLayer)))) {
    if (systemdefault->DriveRemovable()) {
//      printf("I Need to Move\n");
      DeleteFolder(TempFolder);
    }
    delete layer;
  }
//////////////////////////////////////////////////////////////
      lExitCode = dwExitCode;
      return 0;
    } else {
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
/*  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }*/
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
      PostQuitMessage(0);
      return 0;

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
