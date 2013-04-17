#include "run.h"

#include <stdio.h>

extern char * DestFolder;
extern char * tempFile;
extern staticlabel_c * progresslabel;
extern progress_c * progressbar;
extern pages_c * pages;
extern language_c * language;

unziplib_c * zip;
char PackZip[] = "pack.zip";
int cur;
char * fName;

int runIt(HWND wnd, int step) {
  if (step == 0) {
    pages->disableButtons();
    cur = 0;
    progresslabel->setLangId(11); //11
    StripSlash(DestFolder);
    MkDir(DestFolder);
    zip = new unziplib_c;
    memcpy(tempFile+strlen(tempFile), PackZip, strlen(PackZip)+1);
    zip->open(tempFile);
    progressbar->setRange(0,zip->getCount());
    SetTimer(wnd,TIMER_STEP1,250,NULL);
  } else if (step == 1) {
    if (cur < zip->Count) {
      fName = zip->getFileName(cur);
      char * lab = new char[MAX_PATH];
      sprintf(lab,language->getLangText(12),fName);
      progresslabel->setText(lab);
      delete[] lab;
      if ((fName != NULL) && (strlen(fName) > 1)) {
        char * temp = new char[MAX_PATH];
        snprintf(temp,MAX_PATH,"%s\\%s",DestFolder,fName);
        delete[] fName;
        if (zip->isDir(cur)) {
          MkDir(temp);
        } else {
          zip->extractFile(cur,temp);
        }
        delete[] temp;
      }
      cur = cur + 1;
      progressbar->setValue(cur);
      SetTimer(wnd,TIMER_STEP1,250,NULL);
    } else {
      SetTimer(wnd,TIMER_STEP2,250,NULL);
    }
  } else if (step == 2) {
    progresslabel->setLangId(13); //13
    pages->enableButtons();
    pages->prevButton->disable();
  }
  return 0;
}
