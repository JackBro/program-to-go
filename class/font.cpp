#include "font.h"

font_c::font_c()
{
    //ctor
}

font_c::~font_c()
{
    //dtor
}

int font_c::setSize(int aSize) {
  size = aSize;
  return aSize;
}

int font_c::setName(const char * aName) {
  name = new char[strlen(aName)+1];
  memcpy(name,aName,strlen(aName));
  name[strlen(aName)]=0;
  return 0;
}

int font_c::setSizeName(int aSize,const char * aName) {
  setSize(aSize);
  setName(aName);
  return 0;
}


int font_c::create() {
  hFont = CreateFont (-MulDiv(size, GetDeviceCaps(GetDC(0), LOGPIXELSY), 72), 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
	  OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	  DEFAULT_PITCH | FF_DONTCARE, name);
  return 0;
}
