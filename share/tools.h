#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <windows.h>
#include <stdio.h>

int WINAPI GetTempFolderName(char * lpPathName, char * lpPrefixString, int uUnique, char * lpTempFileName);
int CopyFolder(char * from, char * to, HWND wnd);
int DeleteFolder(char * from);
int MkDir(char * sFolder);
char * StripSlash(char * sFolder);
bool FileExists(char * fName);

#endif // TOOLS_H_INCLUDED
