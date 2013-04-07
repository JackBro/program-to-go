#ifndef XMLFILE_H
#define XMLFILE_H

#include "..\..\share\class\textfile.h"
#include "charcollection.h"


class xmlfile_c : public textfile_c
{
    public:
        xmlfile_c();
        virtual ~xmlfile_c();
        bool getXMLTag();
        char * Tag;
        char * TagName;
        char * TagAttrib;
        char * TagString;
        int TagIntger;
        bool OpenReadXMLFile(char * aFile);
        bool OpenWriteXMLFile(char * aFile);
        int OpenXMLGroup(char * text);
        int CloseXMLGroup();
        int CloseXMLFile();
        int CloseWriteXMLFile();
        int WriteStringXML(char * aLabel,char * text);
        int WriteIntergerXML(char * aLabel,int value);
    protected:
    private:
        int strrepl(char *s, int len, const char *search, const char *replace);
        int strins(char *s, int len, char *x, int i);
        int strdel(char *s, int len, int a, int b);
        charcollection_c * xmlgroup;

};


#endif // XMLFILE_H
