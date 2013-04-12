#ifndef EDIT_H
#define EDIT_H

#include "../../share/class/initcontrols.h"


class edit_c : public initcontrols_c
{
    public:
        edit_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~edit_c();
    protected:
    private:
};

#endif // EDIT_H
