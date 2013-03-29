#include "textfile.h"

#if debug
#include <stdio.h>
#endif

textfile_c::textfile_c()
{
    //ctor
}

textfile_c::~textfile_c()
{
    //dtor
}

bool textfile_c::OpenReadTextFile(char * aName) {
  bool ok = OpenReadFile(aName);
  if (ok) {
    buffer = new char[2048];
    bufferStart = 0;
    bufferEnd = 0;
  }
  return ok;
}

int textfile_c::CloseTextFile() {
  delete buffer;
  CloseFile();
  return 0;
}

bool textfile_c::getChar() {
  if (checkBuffer()) {
    currentChar = buffer[bufferStart];
    bufferStart = bufferStart+1;
    return true;
  } else {
    return false;
  }
}

bool textfile_c::checkBuffer() {
  if (bufferEnd <= bufferStart) {
    bufferEnd = readFile(buffer,2048);
    bufferStart = 0;
    buffer[bufferEnd] = 0;
  }
  return bufferEnd > 0;
}

bool textfile_c::OpenWriteTextFile(char * aName) {
  return OpenWriteFile(aName);
}

int textfile_c::WriteTextLine(char * aText) {
  char * text = new char[strlen(aText)+3];
  memcpy(text,aText,strlen(aText));
  text[strlen(aText)] = 13;
  text[strlen(aText)+1] = 10;
  text[strlen(aText)+2] = 0;
  WriteBuffer(text,strlen(text));
  delete text;
  return 0;
}
