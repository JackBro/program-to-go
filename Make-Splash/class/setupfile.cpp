#include "setupfile.h"

#include <stdio.h>

setupfile_c::setupfile_c(const char * aPfad, const char * aFile)
{
  changed = false;
  xml = new tinyxml2::XMLDocument;
  fName = new char[MAX_PATH];
  memcpy(fName,aPfad,strlen(aPfad)+1);
  memcpy(fName+strlen(fName),aFile,strlen(aFile)+1);
  xml->LoadFile(fName);
}

setupfile_c::~setupfile_c()
{
   delete xml;
}

char * setupfile_c::getLang() {
  tinyxml2::XMLElement * data = xml->FirstChildElement("Config");
  char * ret = NULL;
  if (data != NULL) {
    data = data->FirstChildElement("Language");
  }
  if (data != NULL) {
    ret = (char *)data->GetText();
  }
  return ret;
}

int setupfile_c::setLang(const char * aLang) {
  if ((getLang() == NULL) || (strcmp(getLang(),aLang) != 0)) {
    tinyxml2::XMLElement * data = xml->FirstChildElement("Config");
    if (data == NULL) {
      data = xml->NewElement("Config");
      xml->InsertEndChild(data);
    }
    data = data->FirstChildElement("Language");
    if (data == NULL) {
      data = xml->FirstChildElement("Config");
      data->InsertEndChild(xml->NewElement("Language"));
      data = xml->FirstChildElement("Config")->FirstChildElement("Language");
    }
    if (aLang != NULL) data->InsertEndChild(xml->NewText(aLang));
    changed = true;
  }
  return 0;
}

int setupfile_c::checkSave() {
  if (changed) {
    char * folder = new char[MAX_PATH];
    memcpy(folder, fName, strlen(fName)+1);
    StripName(folder);
    StripSlash(folder);
    MkDir(folder);
    delete[] folder;
    xml->SaveFile(fName);
  }
  return 0;
}
