#ifndef RUNCONFIG_H
#define RUNCONFIG_H

#include "..\..\share\class\xmlfile.h"


class runconfig_c : public xmlfile_c
{
    public:
        runconfig_c(char *);
        virtual ~runconfig_c();
        char * ExeFile;
    protected:
      int loadConfig();
      int loadAppData();
    private:
};

#endif // RUNCONFIG_H
