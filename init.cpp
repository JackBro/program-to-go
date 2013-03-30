#include "init.h"

#if Debug
#include <stdio.h>
#endif // Debug

SystemDefault_c * systemdefault;
runconfig_c * runconfig;
char * configfile;
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
  return 0;
}
