#include "tools.h"

int WINAPI GetTempFolderName(char * lpPathName, char * lpPrefixString, int uUnique, char * lpTempFileName) {
  if (uUnique != 0) {
    snprintf(lpTempFileName, MAX_PATH, "%s%s%X\\\0\0", lpPathName, lpPrefixString, uUnique);
  } else {
    uUnique = GetTickCount();
    do {
      uUnique++;
      snprintf(lpTempFileName, MAX_PATH, "%s%s%X\\\0\0", lpPathName, lpPrefixString, uUnique);
    }
    while (!CreateDirectory(lpTempFileName,NULL));
  }
  lpTempFileName[strlen(lpTempFileName)] = 0;
  lpTempFileName[strlen(lpTempFileName)+1] = 0;
  return uUnique;
}

int CopyFolder(char * from, char * to, HWND wnd) {
  SHFILEOPSTRUCT sfo;
  ZeroMemory(&sfo, sizeof(SHFILEOPSTRUCT));
  sfo.hwnd = wnd;
  sfo.wFunc=FO_COPY;
  sfo.fFlags=FOF_SIMPLEPROGRESS | FOF_RENAMEONCOLLISION | FOF_NOERRORUI |
             FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR/**/;
  sfo.lpszProgressTitle="Copy files...";
  sfo.pFrom=from;
  sfo.pTo=to;
  if (1223 == SHFileOperation(&sfo)) {
    return 1;
  }
  return 0;
}

int DeleteFolder(char * from) {
  SHFILEOPSTRUCT sfo;
  ZeroMemory(&sfo, sizeof(SHFILEOPSTRUCT));
  sfo.wFunc=FO_DELETE;
  sfo.fFlags=FOF_SIMPLEPROGRESS | FOF_RENAMEONCOLLISION | FOF_NOERRORUI |
             FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR/**/;
  sfo.lpszProgressTitle="Copy files...";
  sfo.pFrom=from;
  SHFileOperation(&sfo);
}

