#ifndef INITCONTROLS_H
#define INITCONTROLS_H

#if run
#define _WIN32_IE 0x0400
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#include <windows.h>
#include <commctrl.h>
#endif

//#include "language.h"

extern bool ControlsInited;

class initcontrols_c
{
    public:
        initcontrols_c();
        virtual ~initcontrols_c();
        HWND Wnd;
        int setFont(HFONT font);
        int langId;
        int enable();
        int disable();
        virtual int hide();
        virtual int show();
        int setText(char * aText);
        char * getText();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
    protected:

    private:
};

#endif // INITCONTROLS_H
