#include "languagefile.h"

#include <stdio.h>

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

char * languagefile_c::getLabel() {
  char * ret = NULL;
  tinyxml2::XMLElement * data = getDescription();
  if (data != NULL) {
    data = data->FirstChildElement("Label");
  }
  if (data != NULL) {
    ret = (char *)data->GetText();
  }
  return ret;
}

char * languagefile_c::getBase() {
  char * ret = NULL;
  tinyxml2::XMLElement * data = getDescription();
  if (data != NULL) {
    data = data->FirstChildElement("Base");
  }
  if (data != NULL) {
    ret = (char *)data->GetText();
  }
  return ret;
}

char * languagefile_c::getId() {
  char * ret = NULL;
  tinyxml2::XMLElement * data = getDescription();
  if (data != NULL) {
    data = data->FirstChildElement("Id");
  }
  if (data != NULL) {
    ret = (char *)data->GetText();
  }
  return ret;
}

tinyxml2::XMLElement * languagefile_c::getLanguage() {
  return doc->FirstChildElement("LanguageData");
}

tinyxml2::XMLElement * languagefile_c::getList() {
  tinyxml2::XMLElement * ret = NULL;
  tinyxml2::XMLElement * data = getLanguage();
  if (data != NULL) {
    ret = data->FirstChildElement("List");
  }
  return ret;
}

tinyxml2::XMLElement * languagefile_c::getDescription() {
  tinyxml2::XMLElement * ret = NULL;
  tinyxml2::XMLElement * data = getLanguage();
  if (data != NULL) {
    ret = data->FirstChildElement("Description");
  }
  return ret;
}

tinyxml2::XMLElement * languagefile_c::getLangItem(int id) {
  tinyxml2::XMLElement * ret = NULL;
  tinyxml2::XMLElement * data = getList();
  if (data != NULL) {
    char * _id = new char[15];
    snprintf(_id,15,"L%d",id);
    ret = data->FirstChildElement(_id);
    delete[] _id;
  }
  return ret;
}

char * languagefile_c::getText(int id) {
  char * ret = NULL;
  tinyxml2::XMLElement * data = getLangItem(id);
  if (data != NULL) {
    ret = (char*)data->GetText();
  }
  return ret;
}
