#ifndef FILEEDITS_H
#define FILEEDITS_H

#include <windows.h>
#include <shlobj.h>

#include "initcontrols.h"
#include "edit.h"
#include "buttonicon.h"

class fileedits_c : public initcontrols_c
{
    public:
        fileedits_c(HWND hWnd, int Icon, int TextLabel, int left, int top, int width, int height);
        virtual ~fileedits_c();
        virtual int show();
        virtual int hide();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
        virtual int setFont(HFONT font);
        virtual int setText(char * aText);
        virtual int disable();
        virtual int enable();
        int SetGetPfad(cb_getText aProc);
        virtual char * getText();
    protected:
        edit_c * edit;
        buttonicon_c * button;
    private:
        int aTextLabel;
        HWND parent;
        cb_getText getdefPfad;
};

#endif 
