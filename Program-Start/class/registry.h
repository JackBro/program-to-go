#ifndef REGISTRY_H
#define REGISTRY_H

#include <windows.h>

class registry_c
{
    public:
        registry_c();
        virtual ~registry_c();
        int OpenKey(HKEY aKey, char * sKey);
        int QueryValue(char * Value, char * data, DWORD * Size);
        int SetValue(char * Value, char * data);
        int DeleteValue(char * Value);
        int CloseKey();
//        int CloseCurrentUser();
    protected:
      HKEY Key;
    private:
};

#endif // REGISTRY_H
