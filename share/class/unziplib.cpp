#include "unziplib.h"

#include <stdio.h>

char Patter[] = "\\*.*\0";

unziplib_c::unziplib_c()
{
    //ctor
}

unziplib_c::~unziplib_c()
{
    //dtor
}

int unziplib_c::open(char * fName) {
  hz = OpenZip(fName,0);
  return 0;
}

int unziplib_c::close() {
  CloseZip(hz);
  return 0;
}

int unziplib_c::unzipall(char * aFolder) {
  ZIPENTRY ze;
  char * path = new char[MAX_PATH];
  memcpy(path,aFolder,strlen(aFolder)+1);
  GetZipItem(hz,-1,&ze);
  int itemCount = ze.index;
  for (int i=0; i<itemCount; i++) {
    GetZipItem(hz,i,&ze);
    memcpy(path+strlen(aFolder),ze.name,strlen(ze.name)+1);
    UnzipItem(hz,i,path);
  }
  delete[] path;
  return 0;
}
