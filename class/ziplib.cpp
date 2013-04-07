#include "ziplib.h"

#include <stdio.h>

char Patter[] = "\\*.*\0";

ziplib_c::ziplib_c()
{
    //ctor
}

ziplib_c::~ziplib_c()
{
    //dtor
}

int ziplib_c::open(char * fName) {
  hz = CreateZip(fName,0);
  return 0;
}

int ziplib_c::close() {
  CloseZip(hz);
  return 0;
}

int ziplib_c::addFolder(char * fName, char * base) {
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = INVALID_HANDLE_VALUE;

  printf("In %s\n",fName);
  char * serString = new char [MAX_PATH];
  char * aFile = new char[MAX_PATH];
  char * saveName = new char[MAX_PATH];
  memcpy(serString,fName,strlen(fName)+1);
  if (serString[strlen(serString)-1] == '\\') {serString[strlen(serString)-1] = 0;};
  memcpy(serString+strlen(serString),Patter,strlen(Patter)+1);
  printf("SerString %s\n",serString);
  hFind = FindFirstFile(serString, &FindFileData);
  serString[strlen(serString)-3] = 0;
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
        if ((strcmp(FindFileData.cFileName,".")!=0) && (strcmp(FindFileData.cFileName,"..")!=0)) {
          if (strlen(base) == 0) {
            snprintf(aFile,MAX_PATH-1,"%s\%s",serString,FindFileData.cFileName);
            snprintf(saveName,MAX_PATH-1,"%s",FindFileData.cFileName);
          } else {
            snprintf(aFile,MAX_PATH-1,"%s\%s",serString,FindFileData.cFileName);
            snprintf(saveName,MAX_PATH-1,"%s\\%s",base,FindFileData.cFileName);
          }
          ZipAddFolder(hz,saveName);
          addFolder(aFile,saveName);
        }
      } else {
        if (strlen(base) == 0) {
          snprintf(aFile,MAX_PATH-1,"%s%s",serString,FindFileData.cFileName);
          snprintf(saveName,MAX_PATH-1,"%s",FindFileData.cFileName);
        } else {
          snprintf(aFile,MAX_PATH-1,"%s%s",serString,FindFileData.cFileName);
          snprintf(saveName,MAX_PATH-1,"%s\\%s",base,FindFileData.cFileName);
        }
        ZipAdd(hz,saveName,aFile);
      }
    } while (FindNextFile(hFind, &FindFileData) != 0);
  }
  delete[] saveName;
  delete[] aFile;
  delete[] serString;
  return 0;
}
