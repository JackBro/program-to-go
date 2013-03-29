#ifndef LAYER_H
#define LAYER_H

#if run
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#include <windows.h>
#include <stdio.h>
#endif

#include "registry.h"


class layer_c : public registry_c
{
    public:
        layer_c(char * exefile);
        virtual ~layer_c();
//        hkResult CurrUser
    protected:
    private:
};

#endif // LAYER_H
