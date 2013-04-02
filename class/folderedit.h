#ifndef FOLDEREDIT_H
#define FOLDEREDIT_H

#include <windows.h>
#include <shlobj.h>

#include "initcontrols.h"
#include "edit.h";
#include "buttonicon.h";

class folderedit_c : public initcontrols_c
{
    public:
        folderedit_c(HWND hWnd, int Icon, int TextLabel, int left, int top, int width, int height);
        virtual ~folderedit_c();
        virtual int show();
        virtual int hide();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
        virtual int setFont(HFONT font);
        virtual int setText(char * aText);
        virtual char * getText();
    protected:
        edit_c * edit;
        buttonicon_c * button;
    private:
        int aTextLabel;
        HWND parent;
};

#endif // EDIT_H
