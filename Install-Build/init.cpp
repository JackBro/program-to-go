#include "init.h"

#include <stdio.h>

SystemDefault_c * SystemDefault;
language_c * language;
setupfile_c * setup;
controlcollections_c * controls;
font_c * font;
pages_c * pages;
languagebox_c * langlist;
folderedit_c * sourcepath;
folderedit_c * destpath;
staticlabel_c * progresslabel;
progress_c * progressbar;
HWND Wnd;
edit_c * packname;
char * sourcePfad;
char * destPfad;
char * packName;

int * nextButtonClicked() {
  pages->nextPage();
  if (pages->getPage() == 2) {
    sourcePfad = sourcepath->getText();
    destPfad = destpath->getText();
    packName = packname->getText();
    runIt(Wnd ,0);
  }
  return 0;
}

int * prevButtonClicked() {
  pages->prevPage();
  return 0;
}

int init(HWND hwnd) {
  Wnd = hwnd;
  SystemDefault = new SystemDefault_c;
  setup = new setupfile_c(SystemDefault->PrgPath,"config\\config.xml");
  language = new language_c(setup->getLang(), SystemDefault);
  setup->setLang(language->getCurLang());
  controls = new controlcollections_c;
  controls->setLanguage(language);
  font = new font_c;
  font->setSizeName(10,"Tahoma");
  font->create();
  controls->setFont(font);
  pages = new pages_c;
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Language:", 1, 10, 10, 200, 24)));
  langlist = (languagebox_c*)pages->addControl(
    controls->addControl(
       new languagebox_c(hwnd, 10, 35, 370, 12)));
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Folder:", 8, 10, 10, 370, 24)));
  packname = (edit_c*)pages->addControl(
    controls->addControl(
      new edit_c(hwnd, 10, 35, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Folder:", 6, 10, 65, 370, 24)));
  destpath = (folderedit_c*)pages->addControl(
    controls->addControl(
      new folderedit_c(hwnd, ICON_FOLDER, 7, 10, 90, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Folder:", 5, 10, 120, 370, 24)));
  sourcepath = (folderedit_c*)pages->addControl(
    controls->addControl(
      new folderedit_c(hwnd, ICON_FOLDER, 7, 10, 145, 370, 24)));
////////////
  pages->newPage();
  progresslabel = (staticlabel_c*)pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Progress", 10, 10, 10, 370, 65)));
  progressbar = (progress_c*)pages->addControl(
    controls->addControl(
      new progress_c(hwnd, 10, 80, 370, 24)));
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
  SetTimer(hwnd,TIMER_START,10,NULL);
  return 0;
}

int init_second(HWND hwnd) {
  langlist->setLangList();
  controls->setCurLanguage();
////////////
  if (setup->changed) {
    pages->setPage(0);
  } else {
    pages->setPage(1);
  }
////////////
  sourcepath->setText(SystemDefault->PrgPath);
  destpath->setText(SystemDefault->PrgPath);
  return 0;
}

