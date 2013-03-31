#ifndef PAGE_H
#define PAGE_H

#include "../../share/class/collection.h"
#include "../../share/class/initcontrols.h"


class page_c : public collection_c
{
    public:
        page_c();
        virtual ~page_c();
        int show();
        int hide();
    protected:
    private:
};

#endif // PAGE_H
