#include "languagefile.h"

#if debug
#include <stdio.h>
#endif

languagefile_c::languagefile_c() {
  Name = new char[4];
  Name[0] = 0;
  doc = new tinyxml2::XMLDocument;
}

languagefile_c::~languagefile_c(){
  delete[] Name;
  delete doc;
}

int languagefile_c::loadlanguage(char * aFile, char * aName) {
  if (strlen(aName)>0) {
    delete[] Name;
    Name = new char[strlen(aName)+1];
    memcpy(Name,aName,strlen(aName)+1);
  }
  doc->LoadFile( aFile );
  return 0;
}

char * languagefile_c::getText(int id) {
  char * text;
  char * _id = new char[15];
  snprintf(_id,15,"L%d\0",id);
  text = (char*)doc->FirstChildElement("LanguageData")->FirstChildElement("List")->FirstChildElement(_id)->GetText();
  delete[] _id;
  return text;
}

char * languagefile_c::getLabel() {
  return (char*)doc->FirstChildElement("LanguageData")->FirstChildElement("Description")->FirstChildElement("Label")->GetText();
}

char * languagefile_c::getBase() {
  return (char*)doc->FirstChildElement("LanguageData")->FirstChildElement("Description")->FirstChildElement("Base")->GetText();
}

char * languagefile_c::getId() {
  return (char*)doc->FirstChildElement("LanguageData")->FirstChildElement("Description")->FirstChildElement("Id")->GetText();
}
