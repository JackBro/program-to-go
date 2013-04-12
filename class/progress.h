#ifndef PROGRESS_H
#define PROGRESS_H

#include "../../share/class/initcontrols.h"


class progress_c : public initcontrols_c
{
    public:
        progress_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~progress_c();
        int setRange(int min, int max);
        int setValue(int pos);
    protected:
    private:
};

#endif // PROGRESS_H
