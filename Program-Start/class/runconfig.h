#ifndef RUNCONFIG_H
#define RUNCONFIG_H

#include "..\..\share\class\xmlfile.h"


class runconfig_c : public xmlfile_c
{
    public:
        runconfig_c(char *);
        virtual ~runconfig_c();
        char * ExeFile;
        char * ExeLayers;
        int HiLayer;
        int LoLayer;
    protected:
      int loadConfig();
      int loadAppData();
      int loadLayer();
    private:
};

#endif // RUNCONFIG_H
