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
  int itemCount = getCount();
  for (int i=0; i<itemCount; i++) {
    GetZipItem(hz,i,&ze);
    memcpy(path+strlen(aFolder),ze.name,strlen(ze.name)+1);
    UnzipItem(hz,i,path);
  }
  delete[] path;
  return 0;
}

int unziplib_c::extractFile(char * fName, char * fFile) {
  ZIPENTRY ze;
  int itemCount = getCount();
  for (int i=0; i<itemCount; i++) {
    GetZipItem(hz,i,&ze);
    if (strcmp(ze.name, fName) == 0) {
      UnzipItem(hz,i,fFile);
      i = itemCount;
    }
  }
  return 0;
}

int unziplib_c::extractFile(int i, char * fFile) {
  UnzipItem(hz,i,fFile);
  return 0;
}

int unziplib_c::getCount() {
  ZIPENTRY ze;
  GetZipItem(hz,-1,&ze);
  Count = ze.index;
  return Count;
}

char * unziplib_c::getFileName(int i) {
  ZIPENTRY ze;
  GetZipItem(hz,i,&ze);
  char * temp = new char[strlen(ze.name)+1];
  memcpy(temp, ze.name, strlen(ze.name)+1);
  return temp;
}

bool unziplib_c::isDir(int i) {
  ZIPENTRY ze;
  GetZipItem(hz,i,&ze);
  return (ze.attr&FILE_ATTRIBUTE_DIRECTORY)!=0;
}
