#ifndef ZIPLIB_H
#define ZIPLIB_H

#include "../../program-to-go/libs/zip-unzip/zip.h"

class ziplib_c
{
    public:
        ziplib_c();
        virtual ~ziplib_c();
        int open(char * fName);
        int addFolder(char * fName, char * base);
        int close();
    protected:
    private:
      HZIP hz;
};

#endif // ZIP_H
