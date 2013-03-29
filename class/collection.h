#ifndef COLLECTION_H
#define COLLECTION_H

#if run
#include <windows.h>
#endif

typedef void * zeiger;

class collection_c
{
    public:
        int Count;

        collection_c();
        virtual ~collection_c();

        int add(zeiger data);
        zeiger getByIndex(int i);
        int setById(int i,zeiger data);
        int deleteByIndex(int i);
    protected:
    private:
        int Max;
        int ** daten;

        int CheckSize();
};

#endif // COLLECTION_H
