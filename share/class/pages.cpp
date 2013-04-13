#include "pages.h"

pages_c::pages_c()
{
  curpage = 0;
}

pages_c::~pages_c()
{
}

int pages_c::newPage() {
  add(new page_c);
  return 0;
}

int pages_c::nextPage() {
  if (curpage < Count-1) {
    curpage = curpage+1;
    setPage(curpage);
  }
  return 0;
}

int pages_c::prevPage() {
  if (curpage > 0) {
    curpage = curpage-1;
    setPage(curpage);
  }
  return 0;
}

int pages_c::setPage(int aPage) {
  if (aPage == 0) {
    prevButton->disable();
  } else {
    prevButton->enable();
  }
  if (aPage < Count-1) {
    nextButton->enable();
  } else {
    nextButton->disable();
  }
  curpage = aPage;
  page_c * page;
  for (int i=0; i<Count; i++) {
    page = (page_c*)getByIndex(i);
    if (i == curpage) {
      page->show();
    } else {
      page->hide();
    }
  }
  return 0;
}

button_c * pages_c::setPrevButton(button_c * aButton) {
  prevButton = aButton;
  return aButton;
}

button_c * pages_c::setNextButton(button_c * aButton) {
  nextButton = aButton;
  return aButton;
}

button_c * pages_c::setCloseButton(button_c * aButton) {
  closeButton = aButton;
  return aButton;
}

initcontrols_c *  pages_c::addControl(initcontrols_c * aControl) {
  page_c * page = (page_c*)getByIndex(Count-1);
  page->add(aControl);
  return aControl;
}

int pages_c::getPage() {
  return curpage;
}

HWND pages_c::getPrevButtonHwnd() {
  return prevButton->Wnd;
}

HWND pages_c::getNextButtonHwnd() {
  return nextButton->Wnd;
}

HWND pages_c::getCloseButtonHwnd() {
  return closeButton->Wnd;
}

int pages_c::disableButtons() {
  EnableWindow(prevButton->Wnd,false);
  EnableWindow(nextButton->Wnd,false);
  EnableWindow(closeButton->Wnd,false);
  return 0;
}

int pages_c::enableButtons() {
  setPage(curpage);
  EnableWindow(closeButton->Wnd,true);
  return 0;
}
