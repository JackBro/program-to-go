#include "LoadSave.h"

#include "stdio.h"

char * Name = NULL;

int SaveAsData(HWND hwnd, language_c * lang) {
  char * temp = Name;
  if (Name != NULL) {
    Name = NULL;
  }
  SaveData(hwnd, lang);
  if (Name == NULL) {
    Name = temp;
  } else {
    if (temp != NULL) delete[] temp;
  }
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
  }
  return 0;
}
