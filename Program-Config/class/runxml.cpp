#include "runxml.h"

#include <windows.h>

runxml_c::runxml_c(char * fName)
{
    aName = new char[strlen(fName)];
    memcpy(aName, fName, strlen(fName)+1);
    xml = new tinyxml2::XMLDocument;
}

runxml_c::~runxml_c()
{
    delete xml;
}

int runxml_c::setExeFile(char * ExeFile) {
  tinyxml2::XMLElement * data = xml->FirstChildElement("AppData");
  if (data == NULL) {
    xml->InsertEndChild(xml->NewElement("AppData"));
    data = xml->FirstChildElement("AppData");
  }
  data = data->FirstChildElement("ExeFile");
  if (data == NULL) {
    data = xml->FirstChildElement("AppData");
    data->InsertEndChild(xml->NewElement("ExeFile"));
    data = data->FirstChildElement("ExeFile");
  }
  data->InsertEndChild(xml->NewText(ExeFile));
  return 0;
}

int runxml_c::setLayer(char * Layer, int hVersion, int lVersion) {
  tinyxml2::XMLElement * data = xml->FirstChildElement("AppData");
  if (data == NULL) {
    xml->InsertEndChild(xml->NewElement("AppData"));
    data = xml->FirstChildElement("AppData");
  }
  data = data->FirstChildElement("ExeLayer");
  if (data == NULL) {
    data = xml->FirstChildElement("AppData");
    data->InsertEndChild(xml->NewElement("ExeLayer"));
    data = data->FirstChildElement("ExeLayer");
  }
  data->InsertEndChild(xml->NewText(Layer));
  data->SetAttribute("HiVersion", hVersion);
  data->SetAttribute("LoVersion", lVersion);
  return 0;
}

int runxml_c::setSplashFile(char * File, int delay, int hold) {
  tinyxml2::XMLElement * data = xml->FirstChildElement("AppData");
  if (data == NULL) {
    xml->InsertEndChild(xml->NewElement("AppData"));
    data = xml->FirstChildElement("AppData");
  }
  data = data->FirstChildElement("Splash");
  if (data == NULL) {
    data = xml->FirstChildElement("AppData");
    data->InsertEndChild(xml->NewElement("Splash"));
    data = data->FirstChildElement("Splash");
  }
  data->InsertEndChild(xml->NewText(File));
  data->SetAttribute("Delay", delay);
  data->SetAttribute("Post", hold);
  return 0;
}

int runxml_c::save() {
  xml->SaveFile(aName);
  return 0;
}
