#include "progress.h"

progress_c::progress_c(HWND hWnd, int left, int top, int width, int height)
{
   Wnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                      PROGRESS_CLASS,
                      NULL,
                      WS_VISIBLE | WS_CHILD,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
    //ctor
}

progress_c::~progress_c()
{
    //dtor
}

int progress_c::setRange(int min, int max) {
  SendMessage(Wnd, PBM_SETRANGE, 0, MAKELPARAM(min, max));
  return 0;
}

int progress_c::setValue(int pos){
  SendMessage(Wnd, PBM_SETPOS, pos, 0);
  return 0;
}
