#include "run.h"

#include <stdio.h>

extern char * DestFolder;
extern char * tempFile;

int runIt(int step) {
  if (step == 0) {
    printf("Start Install\n");
    printf("temp %s\n",tempFile);
    printf("Dest %s\n",DestFolder);
  }
  return 0;
}
