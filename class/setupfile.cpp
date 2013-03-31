#include "setupfile.h"

#if debug
#include <stdio.h>
#endif

setupfile_c::setupfile_c(const char * aPfad, const char * aFile)
{
  language = new char[24];
  language[0] = 0;
  changed = false;
  fName = new char[strlen(aPfad)+strlen(aFile)+1];
  memcpy(fName,aPfad,strlen(aPfad)+1);
  memcpy(fName+strlen(aPfad),aFile,strlen(aFile)+1);
  load();
}

setupfile_c::~setupfile_c()
{
   delete language;
}

char * setupfile_c::getLang() {
  return language;
}

int setupfile_c::load() {
  if (OpenReadXMLFile(fName)) {
    while (getXMLTag()) {
      if (strcmp(TagName,"Config") == 0) {
        loadConfig();
      } else if (strcmp(TagName,"/Config") == 0) {
        CloseXMLFile();
        return 0;
      }
    }
    CloseXMLFile();
  }
  return 0;
}

int setupfile_c::loadConfig() {
  while (getXMLTag()) {
    if (strcmp(TagName,"Language") == 0) {
      int len = strlen(TagString);
      if (len > 4) {
        len = 4;
      }
      memcpy(language,TagString,len);
      language[len] = 0;
      getXMLTag();
    } else if (strcmp(TagName,"/Config") == 0) {
      return 0;
    }
  }
  return 0;
}

int setupfile_c::setLang(const char * aLang) {
  if (strcmp(language,aLang) != 0) {
    memcpy(language,aLang,strlen(aLang)+1);
    changed = true;
  }
  return 0;
}

int setupfile_c::checkSave() {
  if (changed) {
    if (OpenWriteXMLFile(fName)) {
      char OpenConfig[] = "Config";
      OpenXMLGroup(OpenConfig);
      char Lang[] = "Language";
      WriteStringXML(Lang,language);
      CloseWriteXMLFile();
    }
  }
  return 0;
}
