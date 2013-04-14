#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "../../share/class/initcontrols.h"


class checkbox_c : public initcontrols_c
{
    public:
        checkbox_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~checkbox_c();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
        bool isChecked();
        cb_event onClick;
    protected:
    private:
};

#endif // BUTTON_H
