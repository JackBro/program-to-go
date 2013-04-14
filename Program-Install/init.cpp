#include "init.h"

#include <stdio.h>

//#define run

SystemDefault_c * SysDef;
language_c * language;
button_c * CButton;
char * tempFile;
char langzip[] = "lang.zip";
char packzip[] = "pack.zip";
controlcollections_c * controls;
font_c * font;
pages_c * pages;
languagebox_c * langlist;
folderedit_c * destpath;

int * nextButtonClicked() {
  pages->nextPage();
/*  if (pages->getPage() == 2) {
    sourcePfad = sourcepath->getText();
    destPfad = destpath->getText();
    packName = packname->getText();
    runIt(Wnd ,0);
  }*/
  return 0;
}

int * prevButtonClicked() {
  pages->prevPage();
  return 0;
}


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
// Lokaliesieren der Paketdaten
      tempFile[strlen(tempFile)-strlen(langzip)] = 0;
      memcpy(tempFile+strlen(tempFile),packzip,strlen(packzip)+1);
      intsall_rec * pack = new intsall_rec;
      app->seek(-sizeof(intsall_rec)-lang->aSize,FILE_END);
      app->readFile((char*)pack, sizeof(intsall_rec));
      if (pack->id == install_pack) {
        app->seek(-lang->aSize-pack->aSize,FILE_END);
        f = new file_c;
        sum = pack->aSize - sizeof(intsall_rec);
        f->OpenWriteFile(tempFile);
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


        printf("size %d\n",pack->aSize);
        printf("temp %s\n",tempFile);

      }

      tempFile[strlen(tempFile)-strlen(packzip)] = 0;
      app->CloseFile();
      language = new language_c(tempFile);
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
          new staticlabel_c(hwnd, "Install folder:", 5, 10, 10, 200, 24)));
      destpath = (folderedit_c*)pages->addControl(
        controls->addControl(
          new folderedit_c(hwnd, ICON_FOLDER, 6, 10, 35, 370, 24)));
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
        (button_c*)controls->addControl(CButton));
////////////
      SetTimer(hwnd,TIMER_START,10,NULL);
    } else {
      Msg->setText("No Language Data found !");
    }
  }
  printf("%s\n",SysDef->ExeFile);

  return 0;
}

int init_second(HWND hwnd) {
  langlist->setLangList();
  controls->setCurLanguage();
////////////
  pages->setPage(0);
  return 0;
}
