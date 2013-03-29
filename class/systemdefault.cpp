#include "systemdefault.h"

#ifdef debug
#include <stdio.h>
#endif

SystemDefault_c::SystemDefault_c()
{
  GetModuleFileName(NULL,ExeFile,MAX_PATH);
#ifdef debug
  printf("Exefile %s\n",ExeFile);
#endif
  char slash[2] = "\\";
  strcpy(ExePath,ExeFile);
  while ((strlen(ExePath) > 0) && (strcmp(&ExePath[strlen(ExePath)-1],&slash[0]) != 0)) {
    ExePath[strlen(ExePath)-1] = 0;
  }
#ifdef debug
  printf("ExePath %s\n",ExePath);
#endif
}

SystemDefault_c::~SystemDefault_c()
{
    //dtor
}
