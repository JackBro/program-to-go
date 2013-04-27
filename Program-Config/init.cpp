#include "init.h"

#include <stdio.h>

SystemDefault_c * SystemDefault;
language_c * language;
setupfile_c * setup;
controlcollections_c * controls;
font_c * font;
pages_c * pages;
languagebox_c * langlist;
folderedit_c * installpath;
fileedit_c * runfile;
fileedit_c * splashfile;
dropdownlist_c * version;
staticlabel_c * progresslabel;
progress_c * progressbar;
numedit_c * delay;
numedit_c * hold;
char * prgPfad;
char * prgExefile;
int layer;
HWND Wnd;

char * getPfad() {
  char * temp = installpath->getText();
  if (temp[strlen(temp)-1] == '\\') {temp[strlen(temp)-1] = 0;}
  return temp;
}

int * nextButtonClicked() {
  pages->nextPage();
  if (pages->getPage() == 3) {
    prgPfad = installpath->getText();
    prgExefile = runfile->getText();
    layer = version->getCurSel();
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
       new staticlabel_c(hwnd, "Folder:", 6, 10, 10, 200, 24)));
  installpath = (folderedit_c*)pages->addControl(
    controls->addControl(
      new folderedit_c(hwnd, ICON_FOLDER, 5, 10, 35, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "App:", 7, 10, 75, 200, 24)));
  runfile = (fileedit_c*)pages->addControl(
    controls->addControl(
      new fileedit_c(hwnd, ICON_FILE, 8, 10, 100, 370, 24)));
  runfile->SetGetPfad(&getPfad);
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "App:", 9, 10, 140, 200, 24)));
  version = (dropdownlist_c*)pages->addControl(
    controls->addControl(
      new dropdownlist_c(hwnd, false, 10, 165, 370, 24)));
  version->addEntry("");
  version->addEntry("Windows XP");
  version->addEntry("Windows Vista");
  version->addEntry("Windows 7");
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Splashscreenfile:", 20, 10, 10, 200, 24)));
  splashfile = (fileedit_c*)pages->addControl(
    controls->addControl(
      new fileedit_c(hwnd, ICON_FILE, 21, 10, 35, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Wait:", 22, 10, 75, 370, 24)));
  delay = (numedit_c*)pages->addControl(
    controls->addControl(
       new numedit_c(hwnd, 10, 100, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Hold:", 23, 10, 140, 370, 24)));
  hold = (numedit_c*)pages->addControl(
    controls->addControl(
       new numedit_c(hwnd, 10, 165, 370, 24)));
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
  langlist->setLangList();
  controls->setCurLanguage();
////////////
  if (setup->changed) {
    pages->setPage(0);
  } else {
    pages->setPage(1);
  }
  SetTimer(hwnd,TIMER_START,10,NULL);
  return 0;
}
