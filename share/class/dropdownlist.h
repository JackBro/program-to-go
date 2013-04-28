#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H

#include "initcontrols.h"


class dropdownlist_c : public initcontrols_c
{
    public:
        dropdownlist_c(HWND hWnd, bool sort, int left, int top, int width, int height);
        virtual ~dropdownlist_c();
        int addEntry(char * text);
        int getCurSel();
        int setCurSel(int sel);
    protected:
    private:
};

#endif // DROPDOWNLIST_H
