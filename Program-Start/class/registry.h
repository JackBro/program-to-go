#ifndef REGISTRY_H
#define REGISTRY_H

#include <windows.h>

class c_registry
{
    public:
        c_registry();
        virtual ~c_registry();
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
