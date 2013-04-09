#include "init.h"

#include <stdio.h>

SystemDefault_c * SysDef;
button_c * CButton;

int init(HWND hwnd) {
  SysDef = new SystemDefault_c;
  file_c * app = new file_c();
  intsall_rec lang;
  staticlabel_c * Msg = new staticlabel_c(hwnd,"",-1,10,10,320,20);
  CButton = new button_c(hwnd, "OK", 4, 297, 237, 85, 24);
  if (app->OpenReadFile(SysDef->ExeFile)) {
    app->seek(sizeof(lang),FILE_END);
    app->readFile((char*)&lang, sizeof(lang));
    if (lang.id == install_lang) {
    } else {
      Msg->setText("No Language Data found !");
      printf("No Lang open File\n");
    }
    printf("Can open File\n");
    app->CloseFile();
  } else {
    printf("Can NOT open File\n");
  }
  printf("%s\n",SysDef->ExeFile);

  return 0;
}
