#include "init.h"

#include <stdio.h>

SystemDefault_c * SystemDefault;
language_c * language;
setupfile_c * setup;
controlcollections_c * controls;
font_c * font;
pages_c * pages;
dropdownlist_c * langlist;

int init(HWND hwnd) {
  SystemDefault = new SystemDefault_c;
  setup = new setupfile_c(SystemDefault->PrgPath,"config\\config.xml");
  language = new language_c(setup->getLang(), SystemDefault);
  setup->setLang(language->getCurLang());
  controls = new controlcollections_c;
  font = new font_c;
  font->setSizeName(10,"Tahoma");
  font->create();
  controls->setFont(font);
  pages = new pages_c;
  printf("%s\n%s\n%s\n",SystemDefault->ExeFile,SystemDefault->ExePath,SystemDefault->PrgPath);
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Language:", 1, 10, 10, 200, 24)));
  langlist = (dropdownlist_c*)pages->addControl(
    controls->addControl(
       new dropdownlist_c(hwnd, 10, 35, 370, 12)));
////////////
  pages->newPage();
////////////
  pages->newPage();
////////////
  pages->setPrevButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Back", 2, 107, 237, 85, 24)));
  pages->setNextButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Next", 3, 202, 237, 85, 24)));
  pages->setCloseButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Finish", 4, 297, 237, 85, 24)));
////////////
  language->allLangToCombo(langlist);
  controls->setLanguage(language);
////////////
  if (setup->changed) {
    pages->setPage(0);
  } else {
    pages->setPage(1);
  }
  SetTimer(hwnd,TIMER_START,10,NULL);
  return 0;
}
