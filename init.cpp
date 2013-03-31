#include "init.h"

SystemDefault_c * SystemDefault;
language_c * language;
setupfile_c * setup;
controlcollections_c * controls;
font_c * font;

int init() {
  SystemDefault = new SystemDefault_c;
  setup = new setupfile_c(SystemDefault->ExePath,"config\\config.xml");
  language = new language_c(setup->getLang(), SystemDefault);
  setup->setLang(language->getCurLang());
  controls = new controlcollections_c;
  font = new font_c;
  font->setSizeName(10,"Tahoma");
  font->create();
  controls->setFont(font);
  return 0;
}
