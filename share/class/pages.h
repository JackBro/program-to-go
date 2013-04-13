#ifndef PAGES_H
#define PAGES_H

#include "..\..\share\class\collection.h"
#include "page.h"
#include "button.h"
#include "../../share/class/initcontrols.h"

class pages_c : public collection_c
{
    public:
        pages_c();
        virtual ~pages_c();
        int newPage();
        int setPage(int aPage);
        initcontrols_c * addControl(initcontrols_c * aControl);
        int nextPage();
        int prevPage();
        button_c * setPrevButton(button_c * aButton);
        HWND getPrevButtonHwnd();
        button_c * setNextButton(button_c * aButton);
        HWND getNextButtonHwnd();
        button_c * setCloseButton(button_c * aButton);
        HWND getCloseButtonHwnd();
        int getPage();
        int disableButtons();
        int enableButtons();
        button_c * prevButton;
        button_c * nextButton;
        button_c * closeButton;
    protected:
    private:
        int curpage;
};

#endif // PAGE_H
