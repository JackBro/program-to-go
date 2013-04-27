#ifndef RUNXML_H
#define RUNXML_H

#include "..\..\libs\libxml2\tinyxml2.h"

class runxml_c
{
    public:
        runxml_c(char * fName);
        virtual ~runxml_c();
        int setExeFile(char * ExeFile);
        int setSplashFile(char * File, int delay, int hold);
        int setLayer(char * Layer, int hVersion, int lVersion);
        int save();
    protected:
    private:
        char * aName;
        tinyxml2::XMLDocument * xml;
};

#endif // RUNXML_H
