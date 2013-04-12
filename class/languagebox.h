#ifndef LANGUAGEBOX_H
#define LANGUAGEBOX_H

#include "dropdownlist.h"

class languagebox_c : public dropdownlist_c
{
    public:
        languagebox_c(HWND hWnd, int left, int top, int width, int height);
        virtual ~languagebox_c();
        int selectByText(char * text);
        char * getCurText();
        int setLangList();
    protected:
    private:
};

#endif // DROBDOWNKLIST_H
