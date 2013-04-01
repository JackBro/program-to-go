#ifndef DROBDOWNKLIST_H
#define DROBDOWNKLIST_H

#include "initcontrols.h"

class dropdownlist_c : public initcontrols_c
{
    public:
        dropdownlist_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~dropdownlist_c();
        int addEntry(char * text);
        int selectByText(const char * text);
        int getCurSel();
        char * getCurText();
    protected:
    private:
};

#endif // DROBDOWNKLIST_H
