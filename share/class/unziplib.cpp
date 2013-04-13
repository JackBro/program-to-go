#include "unziplib.h"

#include <stdio.h>

char Patter[] = "\\*.*\0";

unziplib_c::unziplib_c()
{
    //ctor
}

unziplib_c::~unziplib_c()
{
    //dtor
}

int unziplib_c::open(char * fName) {
  hz = OpenZip(fName,0);
  return 0;
}

int unziplib_c::close() {
  CloseZip(hz);
  return 0;
}
