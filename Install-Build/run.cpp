#include "run.h"

#include <stdio.h>

extern SystemDefault_c * SystemDefault;

char zipfile[] = "temp.zip";
char sourceFile[] = "Program-Install\\bin\\Release\\Program-Install.exe\0";
char sourceLang[] = "Program-Install\\lang\\\0";
char installxml[] = "\\setup\\install.xml\0";
char exe[] = ".exe\0";
char * LizensFile;
char * packPfad;
char * tmpFolder;
char * lizensFile;

int runIt(HWND wnd, int step) {
  if (step == 0) {
    pages->disableButtons();
    progressbar->setRange(0, 7);
    progressbar->setValue(0);
    progresslabel->setLangId(9);
//////////
// get Programpacket
//////////
    packPfad = new char[MAX_PATH];
    memcpy(packPfad, destPfad, strlen(destPfad));
    packPfad[strlen(destPfad)] = 0;
    if (packPfad[strlen(packPfad)-1] != '\\') {
      packPfad[strlen(packPfad)+1] = 0;
      packPfad[strlen(packPfad)] = '\\';
    }
    memcpy(packPfad+strlen(packPfad), packName, strlen(packName)+1);
    memcpy(packPfad+strlen(packPfad), exe, strlen(exe)+1);
//////////
// get Quell Exe
//////////
    char * SourceExe = new char[MAX_PATH];
    memcpy(SourceExe, SystemDefault->PrgPath, strlen(SystemDefault->PrgPath));
    SourceExe[strlen(SystemDefault->PrgPath)] = 0;
    SourceExe[strlen(SourceExe)-1] = 0;
    while ((strlen(SourceExe)>0) && (SourceExe[strlen(SourceExe)-1] != '\\')) {SourceExe[strlen(SourceExe)-1] = 0;}
    memcpy(SourceExe+strlen(SourceExe), sourceFile, strlen(sourceFile)+1);
//////////
// Copy File
//////////
    printf("%s\n",SourceExe);
    if (FileExists(SourceExe)) {
      if (CopyFile(SourceExe, packPfad, false) != 0) {
        progressbar->setValue(1);
        SetTimer(wnd,TIMER_STEP1,250,NULL);
      } else {
        progresslabel->setLangId(10);
        pages->enableButtons();
      }
    } else {
      progresslabel->setLangId(11);
      pages->enableButtons();
    }
    delete[] SourceExe;
  } else if (step == 1) {
    progresslabel->setLangId(16);
    LizensFile = new char[MAX_PATH];
    LizensFile[0] = 0;
    if (lizensbox->isChecked()) {
      if (strlen(lizensFile) > strlen(sourcePfad)) {
        memcpy(LizensFile, sourcePfad, strlen(sourcePfad)+1);
        if (LizensFile[strlen(LizensFile)-1] == '\\') {LizensFile[strlen(LizensFile)-1] = 0;}
        memcpy(LizensFile+strlen(LizensFile),lizensFile+strlen(LizensFile),strlen(lizensFile)-strlen(LizensFile)+1);
        if (FileExists(LizensFile)) {
          memcpy(LizensFile,LizensFile+strlen(sourcePfad),strlen(LizensFile)-strlen(sourceFile)+2);
          if (LizensFile[0] == '\\') {memcpy(LizensFile,LizensFile+1,strlen(LizensFile)+1);}
          progressbar->setValue(2);
          SetTimer(wnd,TIMER_STEP2,250,NULL);
        } else {
          progresslabel->setLangId(17);
          pages->enableButtons();
        }
      } else {
        progresslabel->setLangId(17);
        pages->enableButtons();
      }
    } else {
      progressbar->setValue(2);
      SetTimer(wnd,TIMER_STEP2,250,NULL);
    }
  } else if (step == 2) {
    progresslabel->setLangId(18);
    tinyxml2::XMLDocument * doc = new tinyxml2::XMLDocument;
    tinyxml2::XMLElement* Node = doc->NewElement("Install");
    tinyxml2::XMLElement* Node2 = doc->NewElement("Title");
    Node2->InsertEndChild(doc->NewText(packName));
    Node->InsertEndChild(Node2);
    Node2 = doc->NewElement("Lizense");
    Node2->InsertEndChild(doc->NewText(LizensFile));
    Node->InsertEndChild(Node2);
    doc->InsertEndChild(Node);
    char * instxml = new char[MAX_PATH];
    memcpy(instxml,sourcePfad,strlen(sourcePfad)+1);
    if (instxml[strlen(instxml)-1] == '\\') {instxml[strlen(instxml)-1] = 0;}
    memcpy(instxml+strlen(instxml),installxml,strlen(installxml)+1);
    doc->SaveFile(instxml);
    delete doc;
    delete[] instxml;
    delete[] LizensFile;
    progressbar->setValue(3);
    SetTimer(wnd,TIMER_STEP3,250,NULL);
  } else if (step == 3) {
    progresslabel->setLangId(19);
//////////
// TmpFolder
//////////
    tmpFolder = new char[MAX_PATH];
//    memcpy(tmpFolder,SystemDefault->TempPath,strlen(SystemDefault->TempPath)+1);
    tmpFolder[0] = '\\'; tmpFolder[1] = 0;
    GetTempFolderName(tmpFolder,"IB",0,tmpFolder);
    int len = strlen(tmpFolder);
    memcpy(tmpFolder+len,zipfile,strlen(zipfile)+1);
    ziplib_c * zip = new ziplib_c;
    zip->open(tmpFolder);
    zip->addFolder(sourcePfad,"");
    zip->close();
    progressbar->setValue(4);
    SetTimer(wnd,TIMER_STEP4,250,NULL);
  } else if (step == 4) {
    progresslabel->setLangId(20);
    file_c * f = new file_c;
    f->OpenReadWriteFile(packPfad);
    f->seek(0,FILE_END);
    file_c * l = new file_c;
    l->OpenReadFile(tmpFolder);
    char buf[1024];
    int read = 1;
    int sum = 0;
    do {
      read = l->readFile(buf,1024);
      sum = sum + read;
      f->WriteBuffer(buf,read);
    } while (read>0);
    l->CloseFile();
    delete l;
    install_rec data;
    data.id = install_program;
    data.aSize = sum + sizeof(data);
    f->WriteBuffer((char*)&data,sizeof(data));
    f->CloseFile();
    delete f;
    DeleteFile(tmpFolder);
    progressbar->setValue(5);
    SetTimer(wnd,TIMER_STEP5,250,NULL);
  } else if (step == 5) {
//////////
// get Quell Exe
//////////
    progresslabel->setLangId(12);
    char * SourceExe = new char[MAX_PATH];
    memcpy(SourceExe, SystemDefault->PrgPath, strlen(SystemDefault->PrgPath));
    SourceExe[strlen(SystemDefault->PrgPath)] = 0;
    SourceExe[strlen(SourceExe)-1] = 0;
    while ((strlen(SourceExe)>0) && (SourceExe[strlen(SourceExe)-1] != '\\')) {SourceExe[strlen(SourceExe)-1] = 0;}
    memcpy(SourceExe+strlen(SourceExe), sourceLang, strlen(sourceLang)+1);
//////////
// TmpFolder
//////////
    ziplib_c * zip = new ziplib_c;
    zip->open(tmpFolder);
    zip->addFolder(SourceExe,"");
    zip->close();
    progressbar->setValue(6);
    SetTimer(wnd,TIMER_STEP6,250,NULL);
  } else if (step == 6) {
    progresslabel->setLangId(13);
    file_c * f = new file_c;
    f->OpenReadWriteFile(packPfad);
    f->seek(0,FILE_END);
    file_c * l = new file_c;
    l->OpenReadFile(tmpFolder);
    char buf[1024];
    int read = 1;
    int sum = 0;
    do {
      read = l->readFile(buf,1024);
      sum = sum + read;
      f->WriteBuffer(buf,read);
    } while (read>0);
    l->CloseFile();
    delete l;
    install_rec data;
    data.id = install_lang;
    data.aSize = sum + sizeof(data);
    f->WriteBuffer((char*)&data,sizeof(data));
    f->CloseFile();
    delete f;
    DeleteFile(tmpFolder);
    progressbar->setValue(7);
    progresslabel->setLangId(21);
    pages->enableButtons();
  }
  return 0;
}
