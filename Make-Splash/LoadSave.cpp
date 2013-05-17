/*! \file Make-Splash/LoadSave.cpp
 *  \brief Routionen zum Speichern und Laden der Daten
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#include "LoadSave.h"

char * Name = NULL; /**< Speichert den ausgewaelten Dateinamen */

/** \brief Speichert die Datei ab, wenn kein Dateinname bekannt wird der Savedialog geoeffnet
 *
 * \param wnd HWND Handle des Elternfensters
 * \param language language_c* Sprachen
 * \return immer 0
 *
 */
int SaveData(HWND wnd, language_c * language) {
  if (Name == NULL) {
    c_getsavefilename * getName = new c_getsavefilename;
    getName->setFilter(language->getLang(25));
    Name = getName->get();
  }
  if (Name != NULL) {
    tinyxml2::XMLDocument * doc = new tinyxml2::XMLDocument;
    doc->InsertEndChild(doc->NewDeclaration());
    doc->InsertEndChild(doc->NewComment("Make-Splash Data"));
    doc->InsertEndChild(doc->NewElement("Data"));
    tinyxml2::XMLElement * data = doc->FirstChildElement("Data");
    data->InsertEndChild(doc->NewElement("Text"));
    tinyxml2::XMLElement * xpage = data->FirstChildElement("Text");
    xpage->InsertEndChild(doc->NewElement("Name"));
    tinyxml2::XMLElement * field = xpage->FirstChildElement("Name");
    field->InsertEndChild(doc->NewText(progname->getText()));
    xpage->InsertEndChild(doc->NewElement("Version"));
    field = xpage->FirstChildElement("Version");
    field->InsertEndChild(doc->NewText(progversion->getText()));
    xpage->InsertEndChild(doc->NewElement("Message"));
    field = xpage->FirstChildElement("Message");
    field->InsertEndChild(doc->NewText(progmessage->getText()));
    data->InsertEndChild(doc->NewElement("Picture"));
    xpage = data->FirstChildElement("Picture");
    xpage->InsertEndChild(doc->NewElement("Left"));
    field = xpage->FirstChildElement("Left");
    field->InsertEndChild(doc->NewText(leftpic->getText()));
    xpage->InsertEndChild(doc->NewElement("Right"));
    field = xpage->FirstChildElement("Right");
    field->InsertEndChild(doc->NewText(rightpic->getText()));
    data->InsertEndChild(doc->NewElement("Save"));
    xpage = data->FirstChildElement("Save");
    xpage->InsertEndChild(doc->NewText(savefile->getText()));
    doc->SaveFile(Name);
  }
}
