#include "languagefile.h"

#if debug
#include <stdio.h>
#endif

languagefile_c::languagefile_c() {
  Name = new char[4];
  Name[0] = 0;
  label = new char[4];
  label[0] = 0;
  base = new char[4];
  base[0] = 0;
  id = new char[4];
  id[0] = 0;
  data = new charcollection_c;
}

languagefile_c::~languagefile_c(){
  delete[] Name;
  delete[] label;
  delete[] base;
  delete[] id;
  delete[] data;
}

int languagefile_c::loadlanguage(char * aFile, char * aName) {
  if (strlen(aName)>0) {
    delete[] Name;
    Name = new char[strlen(aName)+1];
    memcpy(Name,aName,strlen(aName)+1);
  }
  if (OpenReadXMLFile(aFile)) {
    while (getXMLTag()) {
      if (strcmp(TagName,"LanguageData") == 0) {
        loaddata();
      }
    };
    CloseXMLFile();
  }
  return 0;
}

int languagefile_c::loaddata() {
  while (getXMLTag()) {
    if (strcmp(TagName,"/LanguageData") == 0) {
      return 0;
    } else if (strcmp(TagName,"Description") == 0) {
      loaddescription();
    } else if (strcmp(TagName,"List") == 0) {
      loadlist();
    }
  }
  return 0;
}

int languagefile_c::loaddescription() {
  while (getXMLTag()) {
    if (strcmp(TagName,"/Description") == 0) {
      return 0;
    } else if (strcmp(TagName,"Label") == 0) {
      delete[] label;
      label = new char[strlen(TagString)+1];
      memcpy(label,TagString,strlen(TagString));
      label[strlen(TagString)] = 0;
      getXMLTag();
    } else if (strcmp(TagName,"Base") == 0) {
      delete[] base;
      base = new char[strlen(TagString)+1];
      memcpy(base,TagString,strlen(TagString));
      base[strlen(TagString)] = 0;
      getXMLTag();
    } else if (strcmp(TagName,"Id") == 0) {
      delete[] id;
      id = new char[strlen(TagString)+1];
      memcpy(id,TagString,strlen(TagString));
      id[strlen(TagString)] = 0;
      getXMLTag();
    }
  }
  return 0;
}

int languagefile_c::loadlist() {
  while (getXMLTag()) {
    if (strcmp(TagName,"/List") == 0) {
      return 0;
    } else if (strcmp(TagName,"Entry") == 0) {
      loadentry();
    }
  }
  return 0;
}

int languagefile_c::loadentry() {
  int id = 0;
  char * text = new char[2];
  text[0] = 0;
  while (getXMLTag()) {
    if (strcmp(TagName,"/Entry") == 0) {
      data->addByIndexChar(id,text);
      delete[] text;
      return 0;
    } else if (strcmp(TagName,"Id") == 0) {
      id = TagIntger;
      getXMLTag();
    } else if (strcmp(TagName,"Value") == 0) {
      delete[] text;
      text = new char[strlen(TagString)+1];
      memcpy(text,TagString,strlen(TagString));
      text[strlen(TagString)] = 0;
      getXMLTag();
    }
  }
  delete[] text;
  return 0;
}

char * languagefile_c::getText(int id) {
  return data->getByIndexChar(id);
}
