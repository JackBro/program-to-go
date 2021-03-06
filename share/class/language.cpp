#include "language.h"

#include <stdio.h>
#undef RC_INVOKED
#undef WINVER
#define WINVER 0x0502
#include <Windows.h>
#include <winnls.h>

char lang[] = "lang\\";
char filter[] = "*.xml";

language_c::language_c(char * setupLang, SystemDefault_c * SystemDefault) : collection_c() {
  current = -1;
  langDir = new char[MAX_PATH];
  memcpy(langDir,SystemDefault->PrgPath,strlen(SystemDefault->PrgPath)+1);
  memcpy(langDir+strlen(langDir),lang,strlen(lang)+1);
  char * SerPath = new char[MAX_PATH];
  memcpy(SerPath,langDir,strlen(langDir)+1);
  memcpy(SerPath+strlen(SerPath),filter, strlen(filter)+1);
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind;
  hFind = FindFirstFile(SerPath, &FindFileData);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      LoadLanguageFile(FindFileData.cFileName);
    } while (FindNextFile(hFind,&FindFileData ));
    FindClose(hFind);
  }
  delete[] SerPath;
//////////////////////////////
// Detect Systemdefault
//////////////////////////////
//  setup = aSetup;
  int ConfigLang = hexToInt(setupLang);
  current = getLangID(ConfigLang);
  if (current == -1) {
    int UserLang = GetUserDefaultUILanguage();
    if (current == -1) {current = getLangID(UserLang);}
    if (current == -1) {current = getLangIDMain(PRIMARYLANGID(UserLang));}
    int SysLang = GetSystemDefaultUILanguage();
    if (current == -1) {current = getLangID(SysLang);}
    if (current == -1) {current = getLangIDMain(PRIMARYLANGID(SysLang));}
  }
}

language_c::language_c(char * tempPath) : collection_c() {
  current = -1;
  langDir = new char[MAX_PATH];
  strcpy(langDir,tempPath);
  char * SerPath = new char[MAX_PATH];
  strcpy(SerPath,langDir);
  strcat(SerPath,"*.xml");
  WIN32_FIND_DATA FindFileData;
  HANDLE hFind;
  hFind = FindFirstFile(SerPath, &FindFileData);
  if (hFind != INVALID_HANDLE_VALUE) {
    LoadLanguageFile(FindFileData.cFileName);
    while (FindNextFile(hFind,&FindFileData )) {
      LoadLanguageFile(FindFileData.cFileName);
    }
    FindClose(hFind);
  }
  delete[] SerPath;
//////////////////////////////
// Detect Systemdefault
//////////////////////////////
//  setup = aSetup;
  if (current == -1) {
    int UserLang = GetUserDefaultUILanguage();
    if (current == -1) {current = getLangID(UserLang);}
    if (current == -1) {current = getLangIDMain(PRIMARYLANGID(UserLang));}
    int SysLang = GetSystemDefaultUILanguage();
    if (current == -1) {current = getLangID(SysLang);}
    if (current == -1) {current = getLangIDMain(PRIMARYLANGID(SysLang));}
  }
}

int language_c::LoadLanguageFile(char * aName) {
  char * fName = new char[MAX_PATH];
  memcpy(fName,langDir,strlen(langDir)+1);
  strcat(fName,aName);
  languagefile_c * file = new languagefile_c;
  add((zeiger)file);
  file->loadlanguage(fName,aName);
  delete[] fName;
  return 0;
}

/*int language_c::allLangToCombo(dropdownlist_c * list) {
  languagefile_c * lang;
  for (int i=0; i < Count; i++) {
    lang = (languagefile_c *)getByIndex(i);
    list->addEntry(lang->label);
  }
  lang = (languagefile_c *)getByIndex(current);
  list->selectByText(lang->label);
  return 0;
}*/

language_c::~language_c() {
}

int language_c::getLangIDMain(int lang) {
  int id = -1;
  languagefile_c * file;
  int i=0;
  while ((i<Count) & (id == -1)) {
    file = (languagefile_c*)getByIndex(i);
    if (lang == hexToInt(file->getBase())) {id = i;}
    i = i + 1;
  }
  return id;
}

int language_c::getLangID(int lang) {
  int id = -1;
  languagefile_c * file;
  int i=0;
  while ((i<Count) & (id == -1)) {
    file = (languagefile_c*)getByIndex(i);
    if (lang == hexToInt(file->getId())) {id = i;}
    i = i + 1;
  }
  return id;
}

int language_c::hexToInt(const char * hex) {
  int value = 0;
  int a;
  char HexStr[] = "0123456789ABCDEFabcdef";
  if (hex != NULL) {
    for (int i=0; i<(int)strlen(hex); i++){
      a = 0;
      while ((HexStr[a] != hex[i]) & (a < 26)) {
        a = a + 1;
      }
      if (a>16) {a=a-6;}
      value = value * 16+a;
    }
  }
  return value;
}

char * language_c::getLang(int id) {
  languagefile_c * file = (languagefile_c*)getByIndex(current);
  return (char*)file->getText(id);
}

char * language_c::setCurrentByLabel(char * aLabel) {
  languagefile_c * file;
  for (int i=0; i<Count;i++) {
    file = (languagefile_c*)getByIndex(i);
    if (strcmp(file->getLabel(),aLabel) == 0) {
      current = i;
//      setup->setLang(file->id);
    }
  }
  return aLabel;
}

/*int language_c::setControlText(initcontrols_c * control,int id) {
  languagefile_c * file = (languagefile_c*)getByIndex(current);
  SendMessage(control->Wnd,WM_SETTEXT,0,(LPARAM)file->getText(id));
  return 0;
}*/

char * language_c::getCurLang() {
  if (current != -1) {
    languagefile_c * file = (languagefile_c *)getByIndex(current);
    return file->getId();
  } else {
    char * temp = new char[2];
    temp[0] = 0;
    temp[1] = 0;
    return temp;
  }
}

char * language_c::getLangName(int id) {
  if ((id < Count) && (id >= 0)) {
    languagefile_c * file = (languagefile_c*)getByIndex(id);
    return file->getLabel();
  } else {
    return NULL;
  }
}

char * language_c::getLangText(int id) {
  languagefile_c * file = (languagefile_c*)getByIndex(current);
  return file->getText(id);
}
