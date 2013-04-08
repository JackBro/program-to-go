#ifndef SETUPFILE_H
#define SETUPFILE_H

#include "..\..\..\share\class\xmlfile.h"


class setupfile_c : public xmlfile_c
{
    public:
        setupfile_c(const char * aPfad, const char * aFile);
        virtual ~setupfile_c();
        char * getLang();
        int setLang(const char * aLang);
        int checkSave();
        int load();
        int loadConfig();
        bool changed;
    protected:
    private:
      char * language;
      char * fName;
};

#endif // SETUPFILE_H
