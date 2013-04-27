#include "numedit.h"

numedit_c::numedit_c(HWND hWnd,int left, int top, int width, int height):initcontrols_c()
{
   char * ccc = new char[5000];
   Wnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                      "edit",
                      NULL,
                      WS_VISIBLE | WS_CHILD | ES_LEFT | ES_RIGHT | ES_NUMBER,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
}

numedit_c::~numedit_c()
{
    //dtor
}
