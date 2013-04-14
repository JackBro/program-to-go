#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "../../share/class/initcontrols.h"


class radiobutton_c : public initcontrols_c
{
    public:
        radiobutton_c(HWND hWnd, char * text, int lang, int left, int top, int width, int height);
        virtual ~radiobutton_c();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
        bool isChecked();
        int check(bool state);
        cb_event onClick;
    protected:
    private:
};

#endif // BUTTON_H
