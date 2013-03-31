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
        initcontrols_c * addControl(initcontrols_c * aControl);
        int setLanguage(language_c * lang);
    protected:
        font_c * hFont;
    private:
};

#endif // CONTROLCOLLECTIONS_H
