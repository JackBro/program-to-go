#include "layer.h"

#include <stdio.h>

layer_c::layer_c(char * exefile,char * layer)
{
  OpenKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers");
  data = new char[512];
  DWORD asize = 512;
  if (QueryValue(exefile,data,&asize) == 1) {
    asize = 0;
    data[0] = 0;
  };
  SetValue(exefile, layer);
  value = new char[strlen(exefile)+5];
  sprintf(value,"%s",exefile);
  value[strlen(exefile)] = 0;
}

layer_c::~layer_c()
{
  DeleteValue(value);
  if (strlen(data) > 0) {
    SetValue(value,data);
  }
  CloseKey();
}
