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
        int AppendMenu(int ID,int lang, char * label, menu_c * aMenu);
        int setLanguage(language_c * lang);
        HMENU getHandle();
    protected:
    private:
      int _setLanguage(HMENU _m, language_c * lang);
      HMENU m;
      HWND wnd;
};

#endif // MENU_H
