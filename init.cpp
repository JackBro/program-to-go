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
  configfile = new char[strlen(systemdefault->ExePath)+strlen(conf)+1];
  memcpy(configfile,systemdefault->ExePath,strlen(systemdefault->ExePath));
  memcpy(configfile+strlen(systemdefault->ExePath),conf,strlen(conf));
  configfile[strlen(systemdefault->ExePath)+strlen(conf)] = 0;
#if Debug
//  printf("%s\n%s\n%s\n%s\n",systemdefault->ExePath, configfile, systemdefault->Drive, systemdefault->TempPath);
#endif
  runconfig = new runconfig_c(configfile);
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
