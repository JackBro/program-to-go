#ifndef SETUPFILE_H
#define SETUPFILE_H

#include "..\..\libs\libxml2\tinyxml2.h"
#include "..\..\share\tools.h"

class setupfile_c
{
    public:
        setupfile_c(const char * aPfad, const char * aFile);
        virtual ~setupfile_c();
        char * getLang();
        int setLang(const char * aLang);
        int checkSave();
        bool changed;
    protected:
    private:
      char * fName;
      tinyxml2::XMLDocument * xml;
};

#endif // SETUPFILE_H
