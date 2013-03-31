#include "init.h"

SystemDefault_c * SystemDefault;
language_c * language;
setupfile_c * setup;

int init() {
  SystemDefault = new SystemDefault_c;
  setup = new setupfile_c(SystemDefault->ExePath,"config\\config.xml");
  language = new language_c(setup, SystemDefault);
  return 0;
}
