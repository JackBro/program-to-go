#ifndef UNZIPLIB_H
#define UNZIPLIB_H

#include "../../libs/zip-unzip/unzip.h"

class unziplib_c
{
    public:
        unziplib_c();
        virtual ~unziplib_c();
        int Count;
        int open(char * fName);
        int close();
        int unzipall(char * aFolder);
        int extractFile(char * fName, char * fFile);
        int extractFile(int i, char * fFile);
        int getCount();
        char * getFileName(int i);
        bool isDir(int i);

    protected:
    private:
      HZIP hz;
};

#endif // ZIP_H
