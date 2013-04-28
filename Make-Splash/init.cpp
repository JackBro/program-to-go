#include "init.h"

HWND hwnd;

pages_c * pages;
controlcollections_c * controls;

int * nextButtonClicked() {
  MessageBox(0,"Next","Info",0);
  pages->nextPage();
/*  if (pages->getPage() == 3) {
    prgPfad = installpath->getText();
    prgExefile = runfile->getText();
    layer = version->getCurSel();
    runIt(Wnd ,0);
  }*/
  return 0;
}

int * prevButtonClicked() {
  MessageBox(0,"Prev","Info",0);
  pages->prevPage();
  return 0;
}


int init(HWND wnd) {
  hwnd = wnd;
  SystemDefault_c * SystemDefault = new SystemDefault_c;
  setupfile_c * setup = new setupfile_c(SystemDefault->PrgPath,"config\\config.xml");
  language_c * language = new language_c(setup->getLang(), SystemDefault);
  setup->setLang(language->getCurLang());
  controls = new controlcollections_c;
  controls->setLanguage(language);
  font_c * font = new font_c;
  font->setSizeName(10,"Tahoma");
  font->create();
  controls->setFont(font);
  pages = new pages_c;
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Language:", 1, 10, 10, 200, 24)));
  languagebox_c * langlist = (languagebox_c*)pages->addControl(
    controls->addControl(
       new languagebox_c(hwnd, 10, 35, 370, 12)));
////////////
////////////
  pages->setPrevButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Back", 2, 107, 237, 85, 24)));
  pages->prevButton->onClick = prevButtonClicked;
  pages->setNextButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Next", 3, 202, 237, 85, 24)));
  pages->nextButton->onClick = nextButtonClicked;
  pages->setCloseButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Finish", 4, 297, 237, 85, 24)));
////////////

  return 0;
}
