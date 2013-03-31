#include "language.h"

#if debug
#include <stdio.h>
#endif

language_c::language_c(char * setupLang, SystemDefault_c * SystemDefault) : collection_c() {
  current = -1;
  langDir = new char[MAX_PATH];
  strcpy(langDir,SystemDefault->ExePath);
  strcat(langDir,"lang\\");
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
  delete SerPath;
//////////////////////////////
// Detect Systemdefault
//////////////////////////////
//  setup = aSetup;
  int ConfigLang = hexToInt(setupLang);
  current = getLangID(ConfigLang);
  if (current == -1) {
    int UserLang = /*PRIMARYLANGID(*/GetUserDefaultUILanguage()/*)*/;
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

  delete fName;
  return 0;
}

int language_c::allLangToCombo(dropdownlist_c * list) {
  languagefile_c * lang;
  for (int i=0; i < Count; i++) {
    lang = (languagefile_c *)getByIndex(i);
    list->addEntry(lang->label);
  }
  lang = (languagefile_c *)getByIndex(current);
  list->selectByText(lang->label);
  return 0;
}

language_c::~language_c() {
}

int language_c::getLangIDMain(int lang) {
  int id = -1;
  languagefile_c * file;
  int i=0;
  while ((i<Count) & (id == -1)) {
    file = (languagefile_c*)getByIndex(i);
    if (lang == hexToInt(file->base)) {id = i;}
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
    if (lang == hexToInt(file->id)) {id = i;}
    i = i + 1;
  }
  return id;
}

int language_c::hexToInt(const char * hex) {
  int value = 0;
  int a;
  char HexStr[] = "0123456789ABCDEFabcdef";
  for (int i=0; i<(int)strlen(hex); i++){
    a = 0;
    while ((HexStr[a] != hex[i]) & (a < 26)) {
      a = a + 1;
    }
    if (a>16) {a=a-6;}
    value = value * 16+a;
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
    if (strcmp(file->label,aLabel) == 0) {
      current = i;
//      setup->setLang(file->id);
    }
  }
  return aLabel;
}

int language_c::setControlText(initcontrols_c * control,int id) {
  languagefile_c * file = (languagefile_c*)getByIndex(current);
  SendMessage(control->Wnd,WM_SETTEXT,0,(LPARAM)file->getText(id));
  return 0;
}

char * language_c::getCurLang() {
  if (current != -1) {
    languagefile_c * file = (languagefile_c *)getByIndex(current);
    return file->id;
  } else {
    char * temp = new char[2];
    temp[0] = 0;
    temp[1] = 0;
  }

}
