#ifndef NUMEDIT_H
#define NUMEDIT_H

#include "../../share/class/initcontrols.h"


class numedit_c : public initcontrols_c
{
    public:
        numedit_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~numedit_c();
    protected:
    private:
};

#endif // NUMEDIT_H
