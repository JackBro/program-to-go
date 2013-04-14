#include "file.h"


#include <stdio.h>

file_c::file_c()
{
    //ctor
}

file_c::~file_c()
{
    //dtor
}

bool file_c::OpenReadFile(char * aName) {
  _file = CreateFile(aName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  return ((DWORD)_file != (DWORD)-1);
}

int file_c::CloseFile() {
  if ((DWORD)_file != (DWORD)-1) {
    CloseHandle(_file);
    _file = (HANDLE)INVALID_FILE_ATTRIBUTES;
  }
  return 0;
}

int file_c::readFile(char * buffer,int bufferSize) {
  DWORD bytesRead;
  ReadFile(_file,buffer,bufferSize,&bytesRead,NULL);
  return bytesRead;
}

bool file_c::OpenWriteFile(char * aName) {
  if (CheckDir(aName)) {
    _file = CreateFile(aName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE ,NULL);
    return ((DWORD)_file != (DWORD)-1);
  };
  return false;
}

bool file_c::OpenReadWriteFile(char * aName) {
  if (CheckDir(aName)) {
    _file = CreateFile(aName,GENERIC_WRITE | GENERIC_READ,0,NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);
    return ((DWORD)_file != (DWORD)-1);
  };
  return false;
}

bool file_c::CheckDir(char * aName) {
  int p = strlen(aName)-1;
  while ((p > 0) & (int(aName[p]) != 92)) {
    p--;
  }
  if (p > 1) {
    aName[p] = 0;
    if (DirectoryExists(aName)) {
      aName[p] = 92;
      return true;
    } else {
      if (CheckDir(aName)) {
        CreateDirectory(aName,NULL);
        if (DirectoryExists(aName)) {
          aName[p] = 92;
          return true;
        } else {
          aName[p] = 92;
          return false;
        }
        return DirectoryExists(aName);
      } else {
        aName[p] = 92;
        return false;
      }
    }
  }
  return false;
}

bool file_c::DirectoryExists(const char * aDir)
{
  DWORD dwAttrib = GetFileAttributes(aDir);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int file_c::WriteBuffer(char * buffer, int size) {
  DWORD Written;
  WriteFile(_file,buffer,size,&Written,NULL);
  return 0;
}

int file_c::seek(DWORD aSize, DWORD aPos) {
   SetFilePointer(_file,aSize,NULL,aPos);
  return 0;
}

DWORD file_c::getSize() {
  return GetFileSize(_file,NULL);
}
