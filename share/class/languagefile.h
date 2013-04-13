#ifndef LANGUAGEFILE_H
#define LANGUAGEFILE_H

#include "..\..\libs\libxml2\tinyxml2.h"

class languagefile_c
{
    public:
        languagefile_c();
        virtual ~languagefile_c();
        int loadlanguage(char * aFile, char * aName);
        char * getLabel();
        char * getBase();
        char * getId();
        char * getText(int id);

    protected:
    private:
       char * Name;
       tinyxml2::XMLDocument * doc;
};

#endif // LANGUAGEFILE_H
