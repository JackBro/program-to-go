
#include "tools.h"

int WINAPI GetTempFolderName(char * lpPathName, char * lpPrefixString, int uUnique, char * lpTempFileName)
{
    if (uUnique != 0)
    {
        snprintf(lpTempFileName, MAX_PATH, "%s%s%X\\", lpPathName, lpPrefixString, uUnique);
    }
    else
    {
        uUnique = GetTickCount();
        do
        {
            uUnique++;
            snprintf(lpTempFileName, MAX_PATH, "%s%s%X\\", lpPathName, lpPrefixString, uUnique);
        }
        while (!CreateDirectory(lpTempFileName,NULL));
    }
    lpTempFileName[strlen(lpTempFileName)] = 0;
    lpTempFileName[strlen(lpTempFileName)+1] = 0;
    return uUnique;
}

int CopyFolder(char * from, char * to, HWND wnd)
{
    MSG msg;
    char serfilter[] = "\\*.*\0";
    HANDLE hfind;
    WIN32_FIND_DATA fdata;

    char * myFrom = new char[MAX_PATH];
    char * myTo = new char[MAX_PATH];
    memcpy(myFrom, from, strlen(from)+1);
    memcpy(myTo, to, strlen(to)+1);
    StripSlash(myFrom);
    StripSlash(myTo);

    char * myFilter = new char[MAX_PATH];
    memcpy(myFilter, myFrom, strlen(myFrom)+1);
    memcpy(myFilter+strlen(myFilter),serfilter,strlen(serfilter)+1);

    char * newTo = new char[MAX_PATH];
    char * newFrom = new char[MAX_PATH];

    hfind = FindFirstFile(myFilter,&fdata);
    if (hfind != INVALID_HANDLE_VALUE) {
      do {
        if ((fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
          if ((strcmp(fdata.cFileName,".") != 0) && (strcmp(fdata.cFileName,"..") != 0)) {
            memcpy(newTo, myTo, strlen(myTo)+1);
            newTo[strlen(newTo)+1] = 0; newTo[strlen(newTo)] = '\\';
            memcpy(newTo+strlen(newTo),fdata.cFileName,strlen(fdata.cFileName)+1);
            MkDir(newTo);

            memcpy(newFrom, myFrom, strlen(myFrom)+1);
            newFrom[strlen(newFrom)+1] = 0; newFrom[strlen(newFrom)] = '\\';
            memcpy(newFrom+strlen(newFrom),fdata.cFileName,strlen(fdata.cFileName)+1);

            CopyFolder(newFrom, newTo, wnd);
          }
        } else {
          memcpy(newTo, myTo, strlen(myTo)+1);
          newTo[strlen(newTo)+1] = 0; newTo[strlen(newTo)] = '\\';
          memcpy(newTo+strlen(newTo),fdata.cFileName,strlen(fdata.cFileName)+1);

          memcpy(newFrom, myFrom, strlen(myFrom)+1);
          newFrom[strlen(newFrom)+1] = 0; newFrom[strlen(newFrom)] = '\\';
          memcpy(newFrom+strlen(newFrom),fdata.cFileName,strlen(fdata.cFileName)+1);

          if (!CopyFile(newFrom, newTo, false)) return 1;
        }
        if (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {
          if (GetMessage(&msg, 0, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
          }
        }
      } while(FindNextFile(hfind, &fdata));
      FindClose(hfind);
    }
    delete[] newFrom;
    delete[] newTo;
    delete[] myFilter;
    delete[] myFrom;
    delete[] myTo;
    return 0;
}

int DeleteFolder(char * from)
{
    SHFILEOPSTRUCT sfo;
    ZeroMemory(&sfo, sizeof(SHFILEOPSTRUCT));
    sfo.wFunc=FO_DELETE;
    sfo.fFlags=FOF_SIMPLEPROGRESS | FOF_RENAMEONCOLLISION | FOF_NOERRORUI |
               FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR/**/;
    sfo.lpszProgressTitle="Copy files...";
    sfo.pFrom=from;
    SHFileOperation(&sfo);
    return 0;
}

bool FileExists(char * fName)
{
    bool found = false;
    WIN32_FIND_DATA FindFileData;
    HANDLE handle = FindFirstFile(fName, &FindFileData) ;
    found = handle != INVALID_HANDLE_VALUE;
    if(found)
    {
        FindClose(handle);
    }
    return found;
}

char * StripSlash(char * sFolder) {
  if (sFolder[strlen(sFolder)-1] == '\\') {sFolder[strlen(sFolder)-1] = 0;}
  if (sFolder[strlen(sFolder)-1] == '/') {sFolder[strlen(sFolder)-1] = 0;}
  return sFolder;
}

char * StripName(char * sFolder) {
  while ((strlen(sFolder) > 0 )
         && (sFolder[strlen(sFolder)-1] != '\\')
         && (sFolder[strlen(sFolder)-1] != '/')) {sFolder[strlen(sFolder)-1] = 0;}
  return sFolder;
}

int MkDir(char * sFolder) {
  if (!FileExists(sFolder)) {
    if (!CreateDirectory(sFolder, NULL)) {
      char * aTemp = new char[MAX_PATH];
      memcpy(aTemp,sFolder, strlen(sFolder)-1);
      StripName(aTemp);
      StripSlash(aTemp);
      if (strlen(aTemp) > 0) {MkDir(aTemp);}
      delete[]  aTemp;
      CreateDirectory(sFolder, NULL);
    }
  }
  return 0;
}

