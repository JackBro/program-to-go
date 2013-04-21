#ifndef RUNCONFIG_H
#define RUNCONFIG_H

#include "..\..\share\class\xmlfile.h"
#include "..\..\libs\libxml2\tinyxml2.h"

class runconfig_c : public xmlfile_c
{
    public:
        runconfig_c(char *);
        virtual ~runconfig_c();
        char * ExeFile;
        char * GetExeLayers();
        int GetHiLayer();
        int GetLoLayer();
        char * getSplashName();
        int getSplashDelay();
        int getSplashPost();
    protected:
    private:
      tinyxml2::XMLDocument * doc;
};

#endif // RUNCONFIG_H
