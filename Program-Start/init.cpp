#include "init.h"

#include <stdio.h>

SystemDefault_c * systemdefault;
runconfig_c * runconfig;
char * configfile;
char * appdir;
char * exefile;

char conf[] = "setup\\run.xml";

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
  exefile = new char[strlen(systemdefault->ExePath)+strlen(runconfig->ExeFile)+1];
  memcpy(exefile,systemdefault->ExePath,strlen(systemdefault->ExePath));
  memcpy(exefile+strlen(systemdefault->ExePath),runconfig->ExeFile,strlen(runconfig->ExeFile));
  exefile[strlen(systemdefault->ExePath)+strlen(runconfig->ExeFile)] = 0;
#if Debug
//  printf("%s\n",exefile);
#endif
  appdir = new char[strlen(exefile)+5];
  sprintf(appdir,"%s%s\\\0\0",systemdefault->ExePath,"App");
  appdir[strlen(appdir)] = 0;
  appdir[strlen(appdir)+1] = 0;
  return 0;
}
