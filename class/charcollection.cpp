#include "charcollection.h"

charcollection_c::charcollection_c()
{
    //ctor
}

charcollection_c::~charcollection_c()
{
  int i;
  for(i=0; i<Count; i++) {
    delete getByIndexChar(i);
  }
   return;
}

int charcollection_c::addByIndexChar(int i, char * text) {
  char * temp;
  while (Count <= i) {
    temp = new char[1];
    temp[0] = 0;
    addChar(temp);
    delete temp;
  }
  temp = getByIndexChar(i);
  if (strlen(temp)>3) {
    delete temp;
  }
  temp = new char[strlen(text)+1];
  memcpy(temp,text,strlen(text));
  temp[strlen(text)] = 0;
  setByIdChar(i,temp);
  return 0;
}

int charcollection_c::addChar(char*text) {
  char * temp = new char[strlen(text)+1];
  memcpy(temp,text,strlen(text));
  temp[strlen(text)] = 0;
  return add(text);
}

char * charcollection_c::getByIndexChar(int i) {
  return (char *)getByIndex(i);
}

int charcollection_c::setByIdChar(int i,char * text) {
  return setById(i,text);
}

int charcollection_c::deletByIndexChar(int i) {
  delete getByIndexChar(i);
  deleteByIndex(i);
  return 0;
}
