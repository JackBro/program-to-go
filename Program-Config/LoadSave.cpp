#include "LoadSave.h"

#include "stdio.h"

char * Name = NULL;

int LoadData(HWND hwnd, language_c * lang) {
  char * temp = Name;
  Name = NULL;
  char * filter = lang->getLang(28);
  for (int i=strlen(filter); i>=0; i--) if (filter[i] == ';') filter[i] = 0;
  OPENFILENAME ofn;
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(OPENFILENAME);
  Name = new char[MAX_PATH];
  Name[0] = 0;
  ofn.lpstrFile = Name;
  ofn.hwndOwner = hwnd;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrFilter = filter;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.lpstrDefExt = "conf";
  if (GetOpenFileName(&ofn)) {
    tinyxml2::XMLDocument * doc = new tinyxml2::XMLDocument;
    doc->LoadFile(Name);
    tinyxml2::XMLElement * data = doc->FirstChildElement("Data");
    if (data != NULL) {
      tinyxml2::XMLElement * xpage = data->FirstChildElement("Main");
      if (xpage != NULL) {
        tinyxml2::XMLElement * field = xpage->FirstChildElement("Folder");
        if (field != NULL) {
          installpath->setText((char*)field->GetText());
        }
        field = xpage->FirstChildElement("Exe");
        if (field != NULL) {
          runfile->setText((char*)field->GetText());
        }
        field = xpage->FirstChildElement("Layer");
        if (field != NULL) {
          char * str = (char*)field->GetText();
          int sel = 0;
          for (int i=0; i<strlen(str); str++) {
            if (str[i] == '0') sel = sel * 10 + 0;
            if (str[i] == '1') sel = sel * 10 + 1;
            if (str[i] == '2') sel = sel * 10 + 2;
            if (str[i] == '3') sel = sel * 10 + 3;
            if (str[i] == '4') sel = sel * 10 + 4;
            if (str[i] == '5') sel = sel * 10 + 5;
            if (str[i] == '6') sel = sel * 10 + 6;
            if (str[i] == '7') sel = sel * 10 + 7;
            if (str[i] == '8') sel = sel * 10 + 8;
            if (str[i] == '9') sel = sel * 10 + 9;
          }
          version->setCurSel(sel);
        }
      }
      xpage = data->FirstChildElement("Splash");
      if (xpage != NULL) {
        tinyxml2::XMLElement * field = xpage->FirstChildElement("Pic");
        if (field != NULL) {
          splashfile->setText((char*)field->GetText());
        }
        field = xpage->FirstChildElement("Delay");
        if (field != NULL) {
          delay->setText((char*)field->GetText());
        }
        field = xpage->FirstChildElement("Hold");
        if (field != NULL) {
          hold->setText((char*)field->GetText());
        }
      }
    }
    delete doc;
  }
  if (Name == NULL) {
    Name = temp;
  } else {
    if (temp != NULL) delete[] temp;
  }
  return 0;
}

int SaveAsData(HWND hwnd, language_c * lang) {
  char * temp = Name;
  Name = NULL;
  SaveData(hwnd, lang);
  if (Name == NULL) {
    Name = temp;
  } else {
    if (temp != NULL) delete[] temp;
  }
  return 0;
}

int SaveData(HWND hwnd, language_c * lang) {
  if (Name == NULL) {
    char * filter = lang->getLang(28);
    for (int i=strlen(filter); i>=0; i--) if (filter[i] == ';') filter[i] = 0;
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    Name = new char[MAX_PATH];
    Name[0] = 0;
    ofn.lpstrFile = Name;
    ofn.hwndOwner = hwnd;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = filter;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "conf";
    if (!GetSaveFileName(&ofn)) {
      delete[] Name;
      Name = NULL;
    };
  }
  if (Name != NULL) {
    tinyxml2::XMLDocument * doc = new tinyxml2::XMLDocument;
    doc->InsertEndChild(doc->NewDeclaration());
    doc->InsertEndChild(doc->NewComment("Program-Config Data"));
    doc->InsertEndChild(doc->NewElement("Data"));
    tinyxml2::XMLElement * data = doc->FirstChildElement("Data");
    data->InsertEndChild(doc->NewElement("Main"));
    tinyxml2::XMLElement * xpage = data->FirstChildElement("Main");
    xpage->InsertEndChild(doc->NewElement("Folder"));
    tinyxml2::XMLElement * field = xpage->FirstChildElement("Folder");
    field->InsertEndChild(doc->NewText(installpath->getText()));
    xpage->InsertEndChild(doc->NewElement("Exe"));
    field = xpage->FirstChildElement("Exe");
    field->InsertEndChild(doc->NewText(runfile->getText()));
    xpage->InsertEndChild(doc->NewElement("Layer"));
    field = xpage->FirstChildElement("Layer");
    char * ver = new char[20];
    sprintf(ver, "%d", version->getCurSel());
    if (strcmp("-1", ver)  == 0) {
      ver[0] = '0';
      ver[1] = 0;
    }
    field->InsertEndChild(doc->NewText(ver));
    data->InsertEndChild(doc->NewElement("Splash"));
    xpage = data->FirstChildElement("Splash");
    xpage->InsertEndChild(doc->NewElement("Pic"));
    field = xpage->FirstChildElement("Pic");
    field->InsertEndChild(doc->NewText(splashfile->getText()));
    xpage->InsertEndChild(doc->NewElement("Delay"));
    field = xpage->FirstChildElement("Delay");
    field->InsertEndChild(doc->NewText(delay->getText()));
    xpage->InsertEndChild(doc->NewElement("Hold"));
    field = xpage->FirstChildElement("Hold");
    field->InsertEndChild(doc->NewText(hold->getText()));
    doc->SaveFile(Name);
    delete doc;
  }
  return 0;
}
