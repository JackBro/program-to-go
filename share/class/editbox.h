#ifndef EDITBOX_H
#define EDITBOX_H

#include "../../share/class/initcontrols.h"


class editbox_c : public initcontrols_c
{
    public:
        editbox_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~editbox_c();
    protected:
    private:
};

#endif // EDIT_H
