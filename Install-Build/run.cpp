#include "run.h"

#include <stdio.h>

extern SystemDefault_c * SystemDefault;

char zipfile[] = "lang.zip";
char sourceFile[] = "Program-Install\\bin\\Release\\Program-Install.exe\0";
char sourceLang[] = "Program-Install\\lang\\\0";
char exe[] = ".exe\0";
char * packPfad;
char * tmpFolder;


int runIt(HWND wnd, int step) {
  if (step == 0) {
    pages->disableButtons();
    progressbar->setRange(0,2);
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
    if (FileExists(SourceExe)) {
      if (CopyFile(SourceExe, packPfad, false) != 0) {
        progressbar->setValue(1);
        SetTimer(wnd,TIMER_STEP1,100,NULL);
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
    tmpFolder = new char[MAX_PATH];
    memcpy(tmpFolder,SystemDefault->TempPath,strlen(SystemDefault->TempPath)+1);
    GetTempFolderName(tmpFolder,"IB",0,tmpFolder);
    int len = strlen(tmpFolder);
    memcpy(tmpFolder+len,zipfile,strlen(zipfile)+1);
    ziplib_c * zip = new ziplib_c;
    zip->open(tmpFolder);
    zip->addFolder(SourceExe,"");
    zip->close();
    progressbar->setValue(1);
    SetTimer(wnd,TIMER_STEP2,100,NULL);
  } else if (step == 2) {
    progresslabel->setLangId(13);
    file_c * f = new file_c;
    if (!f->OpenReadWriteFile(packPfad)) {printf("Can not open %d\n", GetLastError());};
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


    printf("%s\n",tmpFolder);
//    printf("%s\n",SourceExe);
    printf("%s\n",packPfad);
    printf("%s\n",SystemDefault->PrgPath);
    pages->enableButtons();
/*    StarterPrg = new char[strlen(prgPfad)+28];
    memcpy(StarterPrg,prgPfad,strlen(prgPfad));
    StarterPrg[strlen(prgPfad)-1] = 0;
    while ((strlen(StarterPrg)>0) & (StarterPrg[strlen(StarterPrg)-1] != '\\')) {StarterPrg[strlen(StarterPrg)-1] = 0;}
    int len = strlen(StarterPrg);
    memcpy(StarterPrg+len,StarterPfad,strlen(StarterPfad));
    StarterPrg[len+strlen(StarterPfad)] = 0;
    if (FileExists(StarterPrg)) {
      progressbar->setValue(1);
      SetTimer(wnd,TIMER_STEP1,100,NULL);
    } else {
      progresslabel->setLangId(12);
      pages->enableButtons();
    }
  } else if (step == 1){
    progresslabel->setLangId(13);
    if (FileExists(prgExefile)) {
      progressbar->setValue(2);
      SetTimer(wnd,TIMER_STEP2,100,NULL);
    } else {
      progresslabel->setLangId(14);
      pages->enableButtons();
    }
  } else if (step == 2){
    progresslabel->setLangId(15);
    runPrg = new char[2*strlen(prgExefile)+5];
    memcpy(runPrg,prgExefile,strlen(prgExefile));
    runPrg[strlen(prgExefile)] = 0;
    while ((strlen(runPrg)>0) & (runPrg[strlen(runPrg)-1] != '\\')) {runPrg[strlen(runPrg)-1] = 0;}
    int len = strlen(runPrg);
    if (strlen(runPrg)>0) {runPrg[strlen(runPrg)-1] = 0;}
    while ((strlen(runPrg)>0) & (runPrg[strlen(runPrg)-1] != '\\')) {runPrg[strlen(runPrg)-1] = 0;}
    memcpy(runPrg+strlen(runPrg),prgExefile+len,strlen(prgExefile));
    runPrg[len+strlen(prgExefile)] = 0;
    StarterPrg[strlen(StarterPrg)+1] = 0;
    runPrg[strlen(runPrg)+1] = 0;
    if (strcmp(StarterPrg,runPrg) != 0) {
      if (CopyFileEx(StarterPrg,runPrg,NULL,NULL,NULL,0)) {
        progressbar->setValue(3);
        SetTimer(wnd,TIMER_STEP3,100,NULL);
      } else {
        progresslabel->setLangId(16);
        pages->enableButtons();
      }
    } else {
      progresslabel->setLangId(16);
      pages->enableButtons();
    }
    delete StarterPrg;
  } else if (step == 3){
    progresslabel->setLangId(17);
    if (setIcon(prgExefile, runPrg) == 0 ) {
      progressbar->setValue(4);
      SetTimer(wnd,TIMER_STEP4,100,NULL);
    } else {
      progresslabel->setLangId(18);
      pages->enableButtons();
    }
    delete runPrg;
  } else if (step == 4){
    progresslabel->setLangId(19);
    char * setupFile = new char [strlen(prgExefile)+25];
    memcpy(setupFile, prgExefile, strlen(prgExefile));
    setupFile[strlen(prgExefile)] = 0;
    while ((strlen(setupFile)>0) && (setupFile[strlen(setupFile)-1] != '\\')) {setupFile[strlen(setupFile)-1] = 0;}
    setupFile[strlen(setupFile)-1] = 0;
    while ((strlen(setupFile)>0) && (setupFile[strlen(setupFile)-1] != '\\')) {setupFile[strlen(setupFile)-1] = 0;}
    memcpy(setupFile+strlen(setupFile),setupPfad,strlen(setupPfad)+1);
    int len = strlen(prgExefile);
    while ((len>0) && (prgExefile[len-1] != '\\')) {len = len-1;}
    len = len - 1;
    while ((len>0) && (prgExefile[len-1] != '\\')) {len = len-1;}
    xmlfile_c * runxml = new xmlfile_c;
    if (runxml->OpenWriteXMLFile(setupFile)) {
      runxml->OpenXMLGroup(AppData);
      runxml->WriteStringXML(ExeFile,prgExefile+len);
      if (layer > 0) {
        runxml->OpenXMLGroup(Layer);
        if (layer == 1) {
          runxml->WriteStringXML(ExeLayer,WinXP);
          runxml->WriteIntergerXML(HiVersion,5);
          runxml->WriteIntergerXML(LoVersion,1);
        }
        if (layer == 2) {
          runxml->WriteStringXML(ExeLayer,WinVista);
          runxml->WriteIntergerXML(HiVersion,6);
          runxml->WriteIntergerXML(LoVersion,0);
        }
        if (layer == 3) {
          runxml->WriteStringXML(ExeLayer,Win7);
          runxml->WriteIntergerXML(HiVersion,6);
          runxml->WriteIntergerXML(LoVersion,1);
        }
      }
      runxml->CloseWriteXMLFile();
      progressbar->setValue(5);
      progresslabel->setLangId(20);
    } else {
      progresslabel->setLangId(21);
    }
    delete setupFile;
    pages->enableButtons();*/
  }
  return 0;
}
