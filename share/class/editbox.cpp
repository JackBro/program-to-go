#include "editbox.h"

editbox_c::editbox_c(HWND hWnd,int left, int top, int width, int height):initcontrols_c()
{
   Wnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                      "EDIT",
                      NULL,
                      WS_VISIBLE | WS_CHILD | ES_LEFT | WS_HSCROLL | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_READONLY,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
}

editbox_c::~editbox_c()
{
    //dtor
}
