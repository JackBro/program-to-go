#include "page.h"

page_c::page_c()
{
    //ctor
}

page_c::~page_c()
{
    //dtor
}

int page_c::hide() {
  initcontrols_c * control;
  for (int i=0; i<Count; i++) {
    control = (initcontrols_c *)getByIndex(i);
    control->hide();
  }
  return 0;
}

int page_c::show() {
  initcontrols_c * control;
  for (int i=0; i<Count; i++) {
    control = (initcontrols_c *)getByIndex(i);
    control->show();
  }
  return 0;
}
