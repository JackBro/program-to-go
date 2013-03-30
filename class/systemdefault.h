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
        char TempPath[MAX_PATH];
<<<<<<< HEAD
        char PrgPath[MAX_PATH];
=======
>>>>>>> 3c701b4182657a77d3f4c867a8d13e31aa099dc4
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
