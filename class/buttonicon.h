#ifndef BUTTONICON_H
#define BUTTONICON_H

#include "../../share/class/initcontrols.h"


class buttonicon_c : public initcontrols_c
{
    public:
        buttonicon_c(HWND hWnd, int icon, int left, int top, int width, int height);
        virtual ~buttonicon_c();
    protected:
    private:
};

#endif // BUTTON_H
