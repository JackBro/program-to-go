#ifndef CHARCOLLECTION_H
#define CHARCOLLECTION_H

#include "collection.h"

class charcollection_c : public collection_c
{
    public:
        charcollection_c();
        virtual ~charcollection_c();
        int addByIndexChar(int i, char * text);
        int addChar(char * text);
        char * getByIndexChar(int i);
        int setByIdChar(int i,char * text);
        int deletByIndexChar(int i);
    protected:
    private:
};

#endif // CHARCOLLECTION_H
