#include "edit.h"

edit_c::edit_c(HWND hWnd,int left, int top, int width, int height):initcontrols_c()
{
   char * ccc = new char[5000];
   char c[] = "this is";
   memcpy(ccc,&c[0],strlen(c));
   ccc[strlen(c)] = 0;
   Wnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                      "edit",
                      NULL,
                      WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOHSCROLL,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
}

edit_c::~edit_c()
{
    //dtor
}
