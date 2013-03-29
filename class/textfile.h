#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "..\..\share\class\file.h"


class textfile_c : public file_c
{
    public:
        textfile_c();
        virtual ~textfile_c();
        bool OpenReadTextFile(char * aName);
        bool OpenWriteTextFile(char * aName);
        int WriteTextLine(char * Text);
        int CloseTextFile();
        bool getChar();
        char currentChar;
    protected:
        char * buffer;
        int bufferStart, bufferEnd;
        bool checkBuffer();
    private:

};

#endif // TEXTFILE_H
