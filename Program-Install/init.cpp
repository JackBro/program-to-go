#include "init.h"

#include <stdio.h>

//#define run

SystemDefault_c * SysDef;
button_c * CButton;
char * tempFile;
char langzip[] = "lang.zip";

int init(HWND hwnd) {
  SysDef = new SystemDefault_c;
  file_c * app = new file_c();
  intsall_rec * lang = new intsall_rec;
  staticlabel_c * Msg = new staticlabel_c(hwnd,"",-1,10,10,320,20);
  CButton = new button_c(hwnd, "OK", 4, 297, 237, 85, 24);
  tempFile = new char[MAX_PATH];
#ifdef run
  memcpy(tempFile,SysDef->TempPath,strlen(SysDef->TempPath)+1);
#else
  tempFile[0] = '\\';
  tempFile[1] = 0;
#endif
  GetTempFolderName(tempFile,"INT",0,tempFile);
  memcpy(tempFile+strlen(tempFile),langzip,strlen(langzip)+1);
  printf("%s\n",tempFile);
#ifdef run
  if (app->OpenReadFile(SysDef->ExeFile)) {
#else
  if (app->OpenReadFile("\\testme.exe\0")) {
#endif
    app->seek(-sizeof(intsall_rec),FILE_END);
    app->readFile((char*)lang, sizeof(intsall_rec));
    if (lang->id == install_lang) {
      app->seek(-lang->aSize,FILE_END);
      file_c * f = new file_c;
      int sum = lang->aSize - sizeof(intsall_rec);
      int read;
      f->OpenWriteFile(tempFile);
      char buf[1024];
      while (sum > 0) {
        if (sum > 1024) {
          read = app->readFile(buf,1024);
        } else {
          read = app->readFile(buf,sum);
        }
        sum = sum - read;
        f->WriteBuffer(buf,read);
      }
      f->CloseFile();
      delete f;
// Entpacken der Sprachdateien
      unziplib_c * zip = new unziplib_c;
      zip->open(tempFile);
      tempFile[strlen(tempFile)-strlen(langzip)] = 0;
      zip->unzipall(tempFile);
      zip->close();
      memcpy(tempFile+strlen(tempFile),langzip,strlen(langzip)+1);
      DeleteFile(tempFile);
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
