#include "setupfile.h"

#if debug
#include <stdio.h>
#endif
#include <windows.h>

setupfile_c::setupfile_c(const char * aPfad, const char * aFile)
{
  changed = false;
  fName = new char[strlen(aPfad)+strlen(aFile)+1];
  memcpy(fName,aPfad,strlen(aPfad)+1);
  memcpy(fName+strlen(aPfad),aFile,strlen(aFile)+1);
  doc = new tinyxml2::XMLDocument;
  doc->LoadFile(fName);
  if (NULL == doc->FirstChildElement("Config")) {
    doc->InsertEndChild(doc->NewElement("Config"));
  }
  if (NULL == doc->FirstChildElement("Config")->FirstChildElement("Language")) {
    doc->FirstChildElement("Config")->InsertEndChild(doc->NewElement("Language"));
  }
}

setupfile_c::~setupfile_c()
{
   delete doc;
}

char * setupfile_c::getLang() {
  char * lang;
  lang = (char*)doc->FirstChildElement("Config")->FirstChildElement("Language")->GetText();
  if (lang == NULL) {
    lang = new char[2];
    lang[0] = 0;
  }
  return lang;
}

int setupfile_c::setLang(const char * aLang) {
  if (strcmp(aLang,getLang()) != 0) {
    doc->FirstChildElement("Config")->FirstChildElement("Language")->InsertEndChild(doc->NewText(aLang));
    changed = true;
  }
  return 0;
}

int setupfile_c::checkSave() {
  if (changed) {
    char * dir = new char[MAX_PATH];
    memcpy(dir,fName,strlen(fName)+1);
    StripName(dir);
    StripSlash(dir);
    MkDir(dir);
    delete[] dir;
    doc->SaveFile(fName);
  }
  return 0;
}
