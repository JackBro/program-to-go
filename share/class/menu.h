#ifndef MENU_H
#define MENU_H

#include <windows.h>
#include "language.h"

class menu_c
{
    public:
        menu_c();
        virtual ~menu_c();
        int setMenu(HWND wnd);
        int Append(int ID,int lang, char * label);
        int setLanguage(language_c * lang);
    protected:
    private:
      HMENU m;
      HWND wnd;
};

#endif // MENU_H
