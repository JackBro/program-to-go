#include "registry.h"

registry_c::registry_c()
{
    //ctor
}

registry_c::~registry_c()
{
    //dtor
}

int registry_c::OpenKey(HKEY aKey, char * sKey) {
  return RegOpenKeyEx(aKey,sKey,NULL,KEY_ALL_ACCESS,&Key);
}

int registry_c::QueryValue(char * Value, char * data, DWORD * Size) {
  if (RegQueryValueEx(Key,Value,NULL,NULL,(LPBYTE)data,Size) == ERROR_SUCCESS) { return 0;};
  return 1;
}

int registry_c::SetValue(char * Value,char * data) {
  RegSetValueEx(Key,Value,NULL,REG_SZ,(LPBYTE)data,strlen(data)+1);
  return 0;
}

int registry_c::DeleteValue(char * Value) {
  RegDeleteValue(Key,Value);
  return 0;
}

int registry_c::CloseKey() {
  RegCloseKey(Key);
  return 0;
}
