#include "run.h"

#include <stdio.h>

char * StarterPrg;
char * ProjectStarter;
char * runPrg;

char StarterPfad[] = "Program-Start\\app\\Program-Start.exe";
char setupPfad[] = "setup\\run.xml";
char appPfad[] = "\\app\\";

int runIt(HWND wnd, int step) {
  if (step == 0) {
    pages->disableButtons();
    progressbar->setRange(0,5);
    progressbar->setValue(0);
    progresslabel->setLangId(11);
    StarterPrg = new char[strlen(prgPfad)+28];
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
    char * setupFile = new char[MAX_PATH];
    memcpy(setupFile,prgExefile, strlen(prgExefile)+1);
    StripName(setupFile);
    StripSlash(setupFile);
    StripName(setupFile);
    memcpy(setupFile+strlen(setupFile),setupPfad,strlen(setupPfad)+1);
    runxml_c * rxml = new runxml_c(setupFile);
    int len = strlen(prgExefile);
    char * xmlexe = new char[MAX_PATH];
    memcpy(xmlexe, prgExefile+strlen(prgPfad)+strlen(appPfad), strlen(prgExefile)+1);
    if (strlen(prgExefile)<= (strlen(prgPfad)+strlen(appPfad))) xmlexe[0] = 0;
    rxml->setExeFile(xmlexe);
    delete[] xmlexe;
    if (layer > 0) {
      if (layer == 1) rxml->setLayer("WINXPSP3", 5, 1);
      if (layer == 2) rxml->setLayer("VISTASP2", 6, 0);
      if (layer == 3) rxml->setLayer("WIN7RTM", 6, 1);
    }
    rxml->save();

    printf("Next: %s\n\n",prgExefile+len);
    printf("Next: %s\n\n",prgExefile);
    delete setupFile;
      pages->enableButtons();
  }
  return 0;
}
