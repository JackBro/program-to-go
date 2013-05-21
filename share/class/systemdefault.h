#ifndef SYSTEMDEFAULT_H
#define SYSTEMDEFAULT_H

#include <windows.h>

class SystemDefault_c
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
        int getCmdCount();
        char * getCmdParam(int i);
    protected:
    private:
      int DriveMode;
      char * CmdLine;
      int CmdCount;
};

#endif // SYSTEMDEFAULT_H
