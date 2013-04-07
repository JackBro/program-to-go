#include "xmlfile.h"

#include <stdio.h>

xmlfile_c::xmlfile_c() {
  //ctor
}

xmlfile_c::~xmlfile_c() {
    //dtor
}

bool xmlfile_c::OpenReadXMLFile(char * aName) {
  bool ok = OpenReadTextFile(aName);
  if (ok) {
    Tag = new char[4096];
    TagName = new char[2];
    memset(TagName,0,2);
    TagAttrib =  new char[2];
    memset(TagAttrib,0,2);
    TagString =  new char[2];
    memset(TagString,0,2);
  }
  return ok;
}

int xmlfile_c::CloseXMLFile() {
  CloseTextFile();
  delete Tag;
  delete TagName;
  delete TagAttrib;
  delete TagString;
  return 0;
}

bool xmlfile_c::getXMLTag() {
  bool ok;
  int pos = 0;
  memset(Tag,0,4096);
  while ((ok = getChar()) & (currentChar != '<')) {
    Tag[pos] = currentChar;
    pos = pos+1;
  };
  if (ok & (strlen(Tag)==0)) {
    ok = getXMLTag();
  }
  if (ok & (Tag[0]== '?')) {
    ok = getXMLTag();
  }
  if (ok & ((int)Tag[0]== 33)) {
    ok = getXMLTag();
  }
  int EndPos = 0;
  int StartPos = 0;
// GetTagName
  if (ok | (strlen(Tag)>0)) {
    while ((EndPos <= (int)strlen(Tag)) & (Tag[EndPos] != '>') & (Tag[EndPos] != ' ')) {
      EndPos = EndPos+1;
    }
    if (EndPos > 0) {
      delete TagName;
      TagName = new char[EndPos+1];
      memcpy(TagName,Tag,EndPos);
      TagName[EndPos] = 0;
      StartPos = EndPos;
    }
// Remove Space for Attrib
    while ((StartPos <= (int)strlen(Tag)) & (Tag[StartPos] == ' ')) {
      StartPos = StartPos+1;
    }
//  Check for Attrib
    if (Tag[StartPos] != '>') {
      EndPos = StartPos;
      while ((EndPos <= (int)strlen(Tag)) & (Tag[EndPos] != '>')) {
        EndPos = EndPos+1;
      }
      delete TagAttrib;
      TagAttrib = new char[EndPos-StartPos+2];
      memcpy(TagAttrib,Tag+StartPos,EndPos-StartPos);
      TagAttrib[EndPos-StartPos] = 0;
      StartPos = EndPos;
    } else {
      delete TagAttrib;
      TagAttrib =  new char[2];
      memset(TagAttrib,0,2);
    }
// Hole TagString
    StartPos = StartPos+1;
    delete TagString;
    TagString = new char[strlen(Tag)-StartPos+2];
    memset(TagString,0,strlen(Tag)-StartPos+1);
    memcpy(TagString,Tag+StartPos,strlen(Tag)-StartPos);
    while ((strlen(TagString)>0) & (((int)TagString[strlen(TagString)-1] == 13) |
                                    ((int)TagString[strlen(TagString)-1] == 9) |
                                    ((int)TagString[strlen(TagString)-1] == 32) |
                                    ((int)TagString[strlen(TagString)-1] == 10))) {
      TagString[strlen(TagString)-1] = 0;
    }
    strrepl(TagString,strlen(TagString)+1,"&uuml;","ü");
    if (strcmp(TagAttrib,"type=\"Integer\"")==0) {
      TagIntger= atoi(TagString);
    } else {
      TagIntger = 0;
    }
  }
  return ok | (strlen(Tag)>0);
}

int xmlfile_c::strrepl(char *s, int len, const char *search, const char *replace)
{
   char *p, *q;
   int slen, alen;

   slen = strlen(s);
   alen = strlen(search);

   p = s;
   do {
      q = strstr(p, search);
      if (!q) break;
      strdel(q, len-(q-s), 0, alen);
      strins(q, len-(q-s), (char *)replace, 0);
      p = q+1;
   } while (p < s+slen);

   return 0;
}

int xmlfile_c::strins(char *s, int len, char *x, int i)
{
   char *p, *q;
   int ls, lx;
   ls = strlen(s);
   lx = strlen(x);
   if ((i < 0) || (i+lx >= len)) return -1;
   if (ls+lx >= len) return -1;

   p = s+ls;
   q = s+ls+lx;
   while (p >= s+i)
      *q-- = *p--;
   p = s+i;
   while (*x)
      *p++ = *x++;
   return (ls+lx);
}

int xmlfile_c::strdel(char *s, int len, int a, int b)
{
   char *p, *q;
   if ((a < 0) || (b < 0)) return -1;
   if ((a > len) || (b > len)) return -1;
   if (a > b) return -1;
   p = s+a;
   q = s+b;
   while (*q) *p++ = *q++;
   *p = 0;
   return (p-s);
}

bool xmlfile_c::OpenWriteXMLFile(char * aFile) {
  bool ok = OpenWriteTextFile(aFile);
  if (ok) {
    xmlgroup = new charcollection_c;
    char head[] = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";
    WriteTextLine(head);
  }
  return ok;
}

int xmlfile_c::OpenXMLGroup(char * aText) {
  xmlgroup->addChar(aText);
  char * text = new char[strlen(aText)+3];
  memcpy(text+1,aText,strlen(aText));
  text[0] = '<';
  text[strlen(aText)+1] = '>';
  text[strlen(aText)+2] = 0;
  WriteTextLine(text);
  delete text;
  return 0;
}

int xmlfile_c::CloseXMLGroup() {
  char * aLabel = xmlgroup->getByIndexChar(xmlgroup->Count-1);
  char * text = new char[strlen(aLabel)+5];
  memcpy(text+2,aLabel,strlen(aLabel));
  text[0] = '<';
  text[1] = '/';
  text[strlen(aLabel)+2] = '>';
  text[strlen(aLabel)+3] = 0;
  WriteTextLine(text);
  delete text;
  xmlgroup->deletByIndexChar(xmlgroup->Count-1);
  return 0;
}

int xmlfile_c::WriteStringXML(char * aLabel,char * atext) {
  char string[] = " type=\"String\">";
  char * text = new char[2*strlen(aLabel)+strlen(string)+strlen(atext)+5];
  memcpy(text+1,aLabel,strlen(aLabel));
  memcpy(text+strlen(aLabel)+1,string,strlen(string));
  memcpy(text+strlen(aLabel)+strlen(string)+1,atext,strlen(atext));
  memcpy(text+strlen(aLabel)+strlen(string)+strlen(atext)+3,aLabel,strlen(aLabel));
  text[0] = '<';
  text[strlen(aLabel)+strlen(string)+strlen(atext)+1] = '<';
  text[strlen(aLabel)+strlen(string)+strlen(atext)+2] = '/';
  text[2*strlen(aLabel)+strlen(string)+strlen(atext)+3] = '>';
  text[2*strlen(aLabel)+strlen(string)+strlen(atext)+4] = 0;
  WriteTextLine(text);
  delete text;
  return 0;
}

int xmlfile_c::WriteIntergerXML(char * aLabel,int value) {
  char string[] = " type=\"Integer\">";
  char * text = new char[256];
  sprintf(text,"<%s type=\"Integer\">%d</%s>",aLabel,value,aLabel);
  WriteTextLine(text);
  delete text;
  return 0;
}

int xmlfile_c::CloseWriteXMLFile() {
  while (xmlgroup->Count > 0) {
    CloseXMLGroup();
  }
  delete xmlgroup;
  CloseFile();
  return 0;
}
