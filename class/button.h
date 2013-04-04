#ifndef BUTTON_H
#define BUTTON_H

#include "../../share/class/initcontrols.h"


class button_c : public initcontrols_c
{
    public:
        button_c(HWND hWnd, const char * text, int lang, int left, int top, int width, int height);
        virtual ~button_c();
        virtual bool event(HWND hwnd, WPARAM wParam, LPARAM lParam);
        cb_event onClick;
    protected:
    private:
};

#endif // BUTTON_H
