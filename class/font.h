#ifndef FONT_H
#define FONT_H

#include <windows.h>

class font_c
{
    public:
        font_c();
        virtual ~font_c();
        int setSize(int aSize);
        int setName(const char * aName);
        int setSizeName(int aSize,const char * aName);
        int create();
        HFONT hFont;
    protected:
    private:
      int size;
      char * name;
};

#endif // FONT_H
