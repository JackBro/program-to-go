#ifndef MENU_H
#define MENU_H

#include <windows.h>

class menu_c
{
    public:
        menu_c();
        virtual ~menu_c();
        int setMenu(HWND wnd);
        int Append(int ID, char * label);
    protected:
    private:
      HMENU m;
};

#endif // MENU_H
