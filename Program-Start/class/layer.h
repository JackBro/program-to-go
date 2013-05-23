#ifndef LAYER_H
#define LAYER_H

#if run
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#include <windows.h>
#include <stdio.h>
#endif

#include "registry.h"


class layer_c : public c_registry
{
    public:
        layer_c(char * exefile,char * layer);
        virtual ~layer_c();
//        hkResult CurrUser
    protected:
        char * data;
        char * value;
    private:
};

#endif // LAYER_H
