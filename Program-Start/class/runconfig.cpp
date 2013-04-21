#include "runconfig.h"

#include <stdio.h>


runconfig_c::runconfig_c(char * fname):xmlfile_c()
{
  ExeFile = new char[10];
  ExeFile[0] = 0;
  doc = new tinyxml2::XMLDocument;
  doc->LoadFile(fname);
  tinyxml2::XMLNode * Node = doc->FirstChildElement("AppData");
  if (Node != NULL) {
    if (NULL != Node->FirstChildElement("ExeFile")) {
      ExeFile = (char*)Node->FirstChildElement("ExeFile")->GetText();
    }
  }
}

runconfig_c::~runconfig_c()
{
    //dtor
}


char * runconfig_c::GetExeLayers() {
  tinyxml2::XMLElement * Node = doc->FirstChildElement("AppData");
  char * temp = NULL;
  if (Node != NULL) {
    Node = Node->FirstChildElement("ExeLayer");
  }
  if (Node != NULL) {
    temp = (char*)Node->GetText();
  }
  return temp;
}

int runconfig_c::GetHiLayer() {
  tinyxml2::XMLElement * Node = doc->FirstChildElement("AppData");
  int temp = 0;
  if (Node != NULL) {
    Node = Node->FirstChildElement("ExeLayer");
  }
  if (Node != NULL) {
    temp = Node->IntAttribute("HiVersion");
  }
  return temp;
}

int runconfig_c::GetLoLayer() {
  tinyxml2::XMLElement * Node = doc->FirstChildElement("AppData");
  int temp = 0;
  if (Node != NULL) {
    Node = Node->FirstChildElement("ExeLayer");
  }
  if (Node != NULL) {
    temp = Node->IntAttribute("LoVersion");
  }
  return temp;
}

char * runconfig_c::getSplashName() {
    tinyxml2::XMLElement * Node = doc->FirstChildElement("AppData");
  char * temp = NULL;
  if (Node != NULL) {
    Node = Node->FirstChildElement("Splash");
  }
  if (Node != NULL) {
    temp = (char*)Node->GetText();
  }
  return temp;
}

int runconfig_c::getSplashDelay() {
  tinyxml2::XMLElement * Node = doc->FirstChildElement("AppData");
  int temp = 500;
  if (Node != NULL) {
    Node = Node->FirstChildElement("Splash");
  }
  if (Node != NULL) {
    temp = Node->IntAttribute("Delay");
  }
  return temp;
}

int runconfig_c::getSplashPost() {
  tinyxml2::XMLElement * Node = doc->FirstChildElement("AppData");
  int temp = 500;
  if (Node != NULL) {
    Node = Node->FirstChildElement("Splash");
  }
  if (Node != NULL) {
    temp = Node->IntAttribute("Post");
  }
  return temp;
}
