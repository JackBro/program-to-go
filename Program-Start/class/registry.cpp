#include "registry.h"

typedef LONG WINAPI (*_RegOpenKeyEx) (HKEY,LPCSTR,DWORD,REGSAM,PHKEY);
typedef LONG WINAPI (*_RegQueryValueEx) (HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
typedef LONG WINAPI (*_RegSetValueEx) (HKEY,LPCSTR,DWORD,DWORD,const BYTE*,DWORD);
typedef LONG WINAPI (*_RegDeleteValue) (HKEY,LPCSTR);
typedef LONG WINAPI (*_RegCloseKey) (HKEY);

HINSTANCE lib = 0;
_RegOpenKeyEx __RegOpenKeyEx = NULL;
_RegQueryValueEx __RegQueryValueEx = NULL;
_RegSetValueEx __RegSetValueEx = NULL;
_RegDeleteValue __RegDeleteValue = NULL;
_RegCloseKey __RegCloseKey = NULL;

c_registry::c_registry()
{
   lib = LoadLibrary("ADVAPI32.DLL");
}

c_registry::~c_registry()
{
}

int c_registry::OpenKey(HKEY aKey, char * sKey) {
  if (__RegOpenKeyEx == NULL) {
    __RegOpenKeyEx = (_RegOpenKeyEx) GetProcAddress (lib, "RegOpenKeyExA") ;
  }
  return __RegOpenKeyEx(aKey,sKey,NULL,KEY_ALL_ACCESS,&Key);
}

int c_registry::QueryValue(char * Value, char * data, DWORD * Size) {
  if (__RegQueryValueEx == NULL) {
    __RegQueryValueEx = (_RegQueryValueEx) GetProcAddress (lib, "RegQueryValueExA") ;
  }
  if (__RegQueryValueEx(Key,Value,NULL,NULL,(LPBYTE)data,Size) == ERROR_SUCCESS) { return 0;};
  return 1;
}

int c_registry::SetValue(char * Value,char * data) {
  if (__RegSetValueEx == NULL) {
    __RegSetValueEx = (_RegSetValueEx) GetProcAddress (lib, "RegSetValueExA") ;
  }
  __RegSetValueEx(Key,Value,NULL,REG_SZ,(LPBYTE)data,strlen(data)+1);
  return 0;
}

int c_registry::DeleteValue(char * Value) {
  if (__RegDeleteValue == NULL) {
    __RegDeleteValue = (_RegDeleteValue) GetProcAddress (lib, "RegDeleteValueA") ;
  }
  __RegDeleteValue(Key,Value);
  return 0;
}

int c_registry::CloseKey() {
  if (__RegCloseKey == NULL) {
    __RegCloseKey = (_RegCloseKey) GetProcAddress (lib, "RegCloseKey") ;
  }
  __RegCloseKey(Key);
  return 0;
}
