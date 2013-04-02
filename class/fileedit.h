#ifndef FILEEDIT_H
#define FILEEDIT_H

#include <windows.h>
#include <shlobj.h>

#include "initcontrols.h"
#include "edit.h";
#include "buttonicon.h";

class fileedit_c : public initcontrols_c
{
    public:
        fileedit_c(HWND hWnd, int Icon, int TextLabel, int left, int top, int width, int height);
        virtual ~fileedit_c();
        virtual int show();
        virtual int hide();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
        virtual int setFont(HFONT font);
        virtual int setText(char * aText);
        int SetGetPfad(cb_getText aProc);
    protected:
        edit_c * edit;
        buttonicon_c * button;
    private:
        int aTextLabel;
        HWND parent;
        cb_getText getdefPfad;
};

#endif // EDIT_H
