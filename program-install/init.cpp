#include "init.h"

#include <stdio.h>

SystemDefault_c * SysDef;
button_c * CButton;

int init(HWND hwnd) {
  SysDef = new SystemDefault_c;
  file_c * app = new file_c();
  intsall_rec * lang = new intsall_rec;
  staticlabel_c * Msg = new staticlabel_c(hwnd,"",-1,10,10,320,20);
  CButton = new button_c(hwnd, "OK", 4, 297, 237, 85, 24);
//  if (app->OpenReadFile(SysDef->ExeFile)) {
  if (app->OpenReadFile("F:\\testme.exe\0")) {
    app->seek(-sizeof(intsall_rec),FILE_END);
    app->readFile((char*)lang, sizeof(intsall_rec));
    if (lang->id == install_lang) {
      printf("%d\n",lang->aSize);
      Msg->setText("Language Data found !");
      printf("Lang open File\n");
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
