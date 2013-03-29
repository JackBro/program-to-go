#include "layer.h"

#include <stdio.h>

layer_c::layer_c(char * exefile)
{
  LARGE_INTEGER asize;
  char * key = new char[strlen(exefile)+40];
  HANDLE hFile = CreateFile(exefile, GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
  GetFileSizeEx(hFile,&asize);
  CloseHandle(hFile);
  exefile = exefile+3;
  sprintf(key,"SIGN.MEDIA=%X",asize);
  sprintf(key,"%s %s",key,exefile);
  for (int i=0; i<strlen(key); i++) {
    if (key[i] == '/') {key[i] = '\\';}
  }
  printf("%s\n%s\n",key,exefile);
}

layer_c::~layer_c()
{
    //dtor
}
