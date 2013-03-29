#include "runconfig.h"

#if debug
#include <stdio.h>
#endif // debug

runconfig_c::runconfig_c(char * fname):xmlfile_c()
{
  ExeFile = new char[10];
  ExeFile[0] = 0;
  ExeLayers = new char[10];
  ExeLayers[0] = 0;
  if (OpenReadXMLFile(fname)) {
    loadConfig();
    CloseXMLFile();
  }  //ctor
}

runconfig_c::~runconfig_c()
{
    //dtor
}

int runconfig_c::loadConfig() {
  while (getXMLTag()) {
    if (strcmp(TagName,"AppData") == 0) {
      loadAppData();
    } else {
//      printf("%s\n",TagName);
    }
  }
  return 0;
}

int runconfig_c::loadAppData() {
  while (getXMLTag()) {
    if (strcmp(TagName,"/AppData") == 0) {
      return 0;
    } else if (strcmp(TagName,"ExeFile") == 0) {
      delete ExeFile;
      ExeFile = new char[strlen(TagString)+1];
      memcpy(ExeFile,TagString,strlen(TagString));
      ExeFile[strlen(TagString)] = 0;
      getXMLTag();
    } else if (strcmp(TagName,"ExeLayer") == 0) {
      delete ExeLayers;
      ExeLayers = new char[strlen(TagString)+1];
      memcpy(ExeLayers,TagString,strlen(TagString));
      ExeLayers[strlen(TagString)] = 0;
      getXMLTag();
    } else {
//      printf("%s\n",TagName);
    }
  }
  return 0;
}
