#ifndef FOLDEREDIT_H
#define FOLDEREDIT_H

#include "../../share/class/initcontrols.h"
#include "edit.h";
#include "buttonicon.h";

class folderedit_c : public initcontrols_c
{
    public:
        folderedit_c(HWND hWnd, int Icon, int left, int top, int width, int height);
        virtual ~folderedit_c();
        virtual int show();
        virtual int hide();
    protected:
        edit_c * edit;
        buttonicon_c * button;
    private:
};

#endif // EDIT_H
