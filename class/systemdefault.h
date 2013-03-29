#ifndef SYSTEMDEFAULT_H
#define SYSTEMDEFAULT_H

#if run
#include <windows.h>
#endif

class SystemDefault_c
{
    public:
        char ExeFile[MAX_PATH];
        char ExePath[MAX_PATH];

        SystemDefault_c();
        virtual ~SystemDefault_c();
    protected:
    private:
};

#endif // SYSTEMDEFAULT_H
