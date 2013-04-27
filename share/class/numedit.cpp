#include "numedit.h"

numedit_c::numedit_c(HWND hWnd,int left, int top, int width, int height):initcontrols_c()
{
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

int numedit_c::setInteger(int value) {
  char * temp = new char[255];
  snprintf(temp,250,"%d",value);
  setText(temp);
  delete[] temp;
  return 0;
}

int numedit_c::getInteger() {
  int res = 0;
  char * txt = getText();
  for (int i=0; i<strlen(txt); i++) {
    if (txt[i] == '0') res = res *10 + 0;
    if (txt[i] == '1') res = res *10 + 1;
    if (txt[i] == '2') res = res *10 + 2;
    if (txt[i] == '3') res = res *10 + 3;
    if (txt[i] == '4') res = res *10 + 4;
    if (txt[i] == '5') res = res *10 + 5;
    if (txt[i] == '6') res = res *10 + 6;
    if (txt[i] == '7') res = res *10 + 7;
    if (txt[i] == '8') res = res *10 + 8;
    if (txt[i] == '9') res = res *10 + 9;
  }
  return res;
}
