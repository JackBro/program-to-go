#include "init.h"

#include <stdio.h>

//#define run

SystemDefault_c * SysDef;
language_c * language;
button_c * CButton;
char * tempFile;
char langzip[] = "lang.zip";
char packzip[] = "pack.zip";
char install[] = "install";
char lizensetxt[] = "lizense.txt";
char mainpfad[] = "Programs-To-Go\\";
char lfile[MAX_PATH];

controlcollections_c * controls;
font_c * font;
pages_c * pages;
languagebox_c * langlist;
folderedit_c * destpath;
char * defPfad;
editbox_c * licensebox;
char * lizens;
radiobutton_c * NoAccept;
radiobutton_c * Accept;

int * nextButtonClicked() {
  pages->nextPage();
  if (pages->getPage() == 2) {
    pages->nextButton->disable();
  } else if (pages->getPage() == 3) {
    printf("Start Install\n");
    printf("temp %s\n",tempFile);
  }
  return 0;
}

int * prevButtonClicked() {
  pages->prevPage();
  return 0;
}

int * licenseButtonClicked() {
  if (Accept->isChecked()) {
    pages->nextButton->enable();
  } else {
    pages->nextButton->disable();
  }
  return 0;
}

int init(HWND hwnd) {
  SysDef = new SystemDefault_c;
  file_c * app = new file_c();
  intsall_rec * lang = new intsall_rec;
  staticlabel_c * Msg = new staticlabel_c(hwnd,"",-1,10,10,420,20);
  CButton = new button_c(hwnd, "OK", 4, 397, 387, 85, 24);
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
        zip->open(tempFile);
        tempFile[strlen(tempFile)-strlen(packzip)] = 0;
        memcpy(tempFile+strlen(tempFile),install,strlen(install)+1);
        zip->extractFile("setup/install.xml", tempFile);
        tinyxml2::XMLDocument * script = new tinyxml2::XMLDocument;
        script->LoadFile(tempFile);
        char * title = (char*)script->FirstChildElement("Install")->FirstChildElement("Title")->GetText();
        lizens = (char*)script->FirstChildElement("Install")->FirstChildElement("Lizense")->GetText();
        SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)title);
        tempFile[strlen(tempFile)-strlen(install)] = 0;
        if (strlen(lizens) > 0) {
          memcpy(tempFile+strlen(tempFile),lizensetxt,strlen(lizensetxt)+1);
          zip->extractFile(lizens, tempFile);
          memcpy(lfile,tempFile,strlen(tempFile)+1);
          tempFile[strlen(tempFile)-strlen(lizensetxt)] = 0;
        }
        zip->close();
        defPfad = new char[MAX_PATH];
        memcpy(defPfad, SysDef->ExePath, 3);
        memcpy(defPfad+3, mainpfad, strlen(mainpfad)+1);
        memcpy(defPfad+strlen(defPfad), title, strlen(title)+1);
      }
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
          new staticlabel_c(hwnd, "Language:", 1, 10, 10, 470, 24)));
      langlist = (languagebox_c*)pages->addControl(
        controls->addControl(
          new languagebox_c(hwnd, 10, 35, 470, 12)));
////////////
      pages->newPage();
      pages->addControl(
        controls->addControl(
          new staticlabel_c(hwnd, "Install folder:", 5, 10, 10, 470, 24)));
      destpath = (folderedit_c*)pages->addControl(
        controls->addControl(
          new folderedit_c(hwnd, ICON_FOLDER, 6, 10, 35, 470, 24)));
////////////
      pages->newPage();
      pages->addControl(
        controls->addControl(
          new staticlabel_c(hwnd, "License:", 7, 10, 10, 470, 24)));
           // Sprache Nummer 7
      licensebox = (editbox_c*)pages->addControl(
        controls->addControl(
          new editbox_c(hwnd, 10, 35, 470, 292)));
      NoAccept = (radiobutton_c*)pages->addControl(
        controls->addControl(
          new radiobutton_c(hwnd, "Do not accept", 8, 15, 330, 465, 24)));
      NoAccept->onClick = licenseButtonClicked;
          // Sprache Nummer 8
      Accept = (radiobutton_c*)pages->addControl(
        controls->addControl(
          new radiobutton_c(hwnd, "Accept", 9,  15, 354, 465, 24)));
      Accept->onClick = licenseButtonClicked;
////////////
      pages->newPage();
////////////
      pages->setPrevButton(
        (button_c*)controls->addControl(
          new button_c(hwnd, "Back", 2, 207, 387, 85, 24)));
      pages->prevButton->onClick = prevButtonClicked;
      pages->setNextButton(
        (button_c*)controls->addControl(
          new button_c(hwnd, "Next", 3, 302, 387, 85, 24)));
      pages->nextButton->onClick = nextButtonClicked;
      pages->setCloseButton(
        (button_c*)controls->addControl(CButton));
////////////
      SetTimer(hwnd,TIMER_START,10,NULL);
    } else {
      Msg->setText("No Language Data found !");
    }
  }
//  printf("%s\n",SysDef->ExeFile);

  return 0;
}

int init_second(HWND hwnd) {
  langlist->setLangList();
  controls->setCurLanguage();
////////////
  if (strlen(lizens) > 0) {
    licensebox->setText(lfile);
    file_c * f = new file_c;
    f->OpenReadFile(lfile);
    DWORD aSize = f->getSize();
    char * text = new char[aSize+1];
    aSize = f->readFile(text, aSize);
    text[aSize] = 0;
    delete f;
    licensebox->setText(text);
    delete[] text;
  }
  pages->setPage(0);
  NoAccept->check(true);
///////////
  destpath->setText(defPfad);
  delete[] defPfad;

  return 0;
}
