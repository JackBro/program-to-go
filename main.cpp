#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

#include "init.h";

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
  STARTUPINFO info={sizeof(info)};
  PROCESS_INFORMATION processInfo;
  CreateProcess( exefile, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
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
