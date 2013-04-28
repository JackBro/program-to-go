#ifndef CONTROLCOLLECTIONS_H
#define CONTROLCOLLECTIONS_H

#include "../../share/class/collection.h"
#include "../../share/class/font.h"
#include "../../share/class/initcontrols.h"
#include "../../share/class/language.h"

class controlcollections_c : public collection_c
{
    public:
        controlcollections_c();
        virtual ~controlcollections_c();
        int setFont(font_c * hFont);
        int setLanguage(language_c * aLang);
        initcontrols_c * addControl(initcontrols_c * aControl);
        int setCurLanguage();
        int event(HWND hwnd, WPARAM wParam, LPARAM lParam);
    protected:
        font_c * hFont;
        language_c * hLang;
    private:
};

#endif // CONTROLCOLLECTIONS_H
