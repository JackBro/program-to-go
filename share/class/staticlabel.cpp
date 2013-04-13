#include "staticlabel.h"

staticlabel_c::staticlabel_c(HWND hWnd, const char * text, int lang, int left, int top, int width, int height)
{
   Wnd = CreateWindow("STATIC",
                      text,
                      WS_VISIBLE | WS_CHILD,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
  langId = lang;
}

staticlabel_c::~staticlabel_c()
{
    //dtor
}
