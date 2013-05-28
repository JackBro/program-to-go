#include "commandline.h"

#include <stdio.h>
#include <windows.h>

c_commandline::c_commandline()
{
  int len = strlen(GetCommandLine());
  cmdline = new char[len+1];
  memcpy(cmdline,GetCommandLine(),len+1);
  cmdcount = -1;
  printf("%d %s =%s=\n",len,cmdline,cmdGetParams());
}

c_commandline::~c_commandline()
{
  delete[] cmdline;
}

int c_commandline::cmdGetCount() {
  if (cmdcount == -1) {
    int c = 0;
    char * pos = cmdline;
    bool quotes;
    while (strlen(pos)>0) {
      quotes = hasQuotes(pos);
      if (quotes) {
        pos = pos + 1;
        while ((strlen(pos) > 0) && (pos[0] != '\"')) {
          pos = pos + 1;
        }
        pos = pos + 1;
      } else {
        while ((strlen(pos) > 0) && (pos[0] != ' ')) {
          pos = pos + 1;
        }
      }
      while ((strlen(pos) > 0) && (pos[0] == ' ')) {
        pos = pos + 1;
      }
      c++;
    }
    cmdcount = c;
  }
  return cmdcount;
}

bool c_commandline::hasQuotes(char * ch)
{
  return ch[0] == '\"';
}

char * c_commandline::cmdGetParams()
{
  if (cmdGetCount() > 1) {
    char * pos = cmdline;
    bool quotes = hasQuotes(pos);
    if (quotes) {
      pos = pos + 1;
      while ((strlen(pos) > 0) && (pos[0] != '\"')) {
        pos = pos + 1;
      }
      pos = pos + 1;
    } else {
      while ((strlen(pos) > 0) && (pos[0] != ' ')) {
        pos = pos + 1;
      }
    }
    while ((strlen(pos) > 0) && (pos[0] == ' ')) {
      pos = pos + 1;
    }
    return pos;
  } else return NULL;
}
