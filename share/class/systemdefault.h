#ifndef SYSTEMDEFAULT_H
#define SYSTEMDEFAULT_H

#include <windows.h>
#include "commandline.h"

class SystemDefault_c : public c_commandline
{
    public:
        char ExeFile[MAX_PATH];
        char ExePath[MAX_PATH];
        char TempPath[MAX_PATH];
        char PrgPath[MAX_PATH];
        char Drive[4];
        SystemDefault_c();
        virtual ~SystemDefault_c();
        bool DriveRemovable();
        int HiVersion;
        int LoVersion;
    protected:
    private:
      int DriveMode;
};

#endif // SYSTEMDEFAULT_H
