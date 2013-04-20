#include "init.h"

#include <stdio.h>

SystemDefault_c * systemdefault;
runconfig_c * runconfig;
char * configfile;
char * appdir;
char * exefile;

char conf[] = "setup\\run.xml";
char app[] = "app\\\0";

int init() {
  systemdefault = new SystemDefault_c;
  configfile = new char[MAX_PATH];
  memcpy(configfile,systemdefault->PrgPath,strlen(systemdefault->PrgPath)+1);
  memcpy(configfile+strlen(configfile),conf,strlen(conf)+1);
  runconfig = new runconfig_c(configfile);
  if (strlen(runconfig->ExeFile) == 0) {
    MessageBox(0,"Can not read \"setup/run.xml\"","Error",MB_ICONERROR);
    return 1;
  }
  exefile = new char[MAX_PATH];
  memcpy(exefile,systemdefault->PrgPath,strlen(systemdefault->PrgPath)+1);
  memcpy(exefile+strlen(exefile),app,strlen(app)+1);
  memcpy(exefile+strlen(exefile), runconfig->ExeFile, strlen(runconfig->ExeFile)+1);
  appdir = new char[MAX_PATH];
  memcpy(appdir,exefile,strlen(exefile)+1);
  StripName(appdir);
  StripSlash(appdir);
  return 0;
}
