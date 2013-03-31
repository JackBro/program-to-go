#ifndef LANGUAGEFILE_H
#define LANGUAGEFILE_H

#include "..\..\share\class\xmlfile.h"
#include "..\..\share\class\charcollection.h"


class languagefile_c : public xmlfile_c
{
    public:
        languagefile_c();
        virtual ~languagefile_c();
        int loadlanguage(char * aFile, char * aName);
        int loaddata();
        int loaddescription();
        int loadlist();
        int loadentry();
        char * label;
        char * base;
        char * id;
        char * getText(int id);
    protected:
    private:
       char * Name;
       charcollection_c * data;
};

#endif // LANGUAGEFILE_H
