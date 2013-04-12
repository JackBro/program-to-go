#ifndef STATICLABEL_H
#define STATICLABEL_H

#include "../../share/class/initcontrols.h"


class staticlabel_c : public initcontrols_c
{
    public:
        staticlabel_c(HWND hWnd, const char * text, int lang, int left, int top, int width, int height);
        virtual ~staticlabel_c();
    protected:
    private:
};

#endif // STATICLABEL_H
