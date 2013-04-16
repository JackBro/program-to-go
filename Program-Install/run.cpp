#include "run.h"

#include <stdio.h>

extern char * DestFolder;
extern char * tempFile;
extern staticlabel_c * progresslabel;
extern progress_c * progressbar;
extern pages_c * pages;

unziplib_c * zip;
char PackZip[] = "pack.zip";
int cur;
char * fName;

int runIt(HWND wnd, int step) {
  if (step == 0) {
    pages->disableButtons();
    cur = 0;
    progresslabel->setLangId(8); //11
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
    }
//    printf("Start Install\n");
//    printf("temp %s\n",tempFile);
//    printf("Dest %s\n",DestFolder);
  }
  return 0;
}
