#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "../share/class/systemdefault.h"
#include "../share/tools.h"
#include "class/runconfig.h"

extern char * exefile;
extern char * appdir;
extern SystemDefault_c * systemdefault;
extern runconfig_c * runconfig;

int init();

#endif // INIT_H_INCLUDED
