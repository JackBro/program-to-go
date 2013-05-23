#include "systemdefault.h"

#ifdef debug
#include <stdio.h>
#endif

#define PARAM_MAX 32;
typedef char * pchar;

SystemDefault_c::SystemDefault_c()
{
  GetModuleFileName(NULL,ExeFile,MAX_PATH);
  char slash[2] = "\\";
  strcpy(ExePath,ExeFile);
  while ((strlen(ExePath) > 0) && (strcmp(&ExePath[strlen(ExePath)-1],&slash[0]) != 0)) {
    ExePath[strlen(ExePath)-1] = 0;
  }
  memcpy(Drive,ExeFile,3);
  Drive[3] = 0;
  GetCurrentDirectory(MAX_PATH,PrgPath);
  PrgPath[strlen(PrgPath)+1] = 0;
  PrgPath[strlen(PrgPath)] = '\\';
  DriveMode = GetDriveType(Drive);
  GetTempPath(MAX_PATH, TempPath);
  _OSVERSIONINFOA Version;
  Version.dwOSVersionInfoSize = sizeof(_OSVERSIONINFOA);
  GetVersionEx(&Version);
  HiVersion = Version.dwMajorVersion;
  LoVersion = Version.dwMinorVersion;
  CmdLine = GetCommandLine();
  CmdCount = -1;
}

SystemDefault_c::~SystemDefault_c()
{
    //dtor
}

bool SystemDefault_c::DriveRemovable() {
  return (DRIVE_CDROM == DriveMode) || (DRIVE_REMOVABLE == DriveMode);
}

int SystemDefault_c::getCmdCount() {
  int c = 0;
  if (CmdCount == -1) {
    char * pos = CmdLine;
    bool useFuss = false;
    while (strlen(pos)>0) {
      useFuss = pos[0] == '\"';
      if (useFuss) {
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
    CmdCount = c;
  } else {
    c = CmdCount;
  }
  return c;
}

char * SystemDefault_c::getCmdParam(int i) {
  char * pos = CmdLine;
  char * start;
  if (i<getCmdCount()) {
    int c = 0;
    start = pos;
    while ((c < i) && (strlen(pos)>0)) {
      bool useFuss = false;
      useFuss = pos[0] == '\"';
      if (useFuss) {
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
      start = pos;
    }
  }
  if (start != NULL) {
    char * ende = start;
    bool useFuss = ende[0] == '\"';
    if (useFuss) {
      ende = ende + 1;
      while ((strlen(ende) > 0) && (ende[0] != '\"')) {
        ende = ende + 1;
      }
      ende = ende + 1;
    } else {
      while ((strlen(ende) > 0) && (ende[0] != ' ')) {
        ende = ende + 1;
      }
    }
    int len = strlen(start)-strlen(ende);
    char * ret = new char[len+1];
    useFuss = start[0] == '\"';
    if (useFuss) {
      memcpy(ret,start+1,len-1);
      ret[len-2] = 0;
    } else {
      memcpy(ret,start,len);
      ret[len] = 0;
    }
    return ret;
  }
  return NULL;
}

char * SystemDefault_c::getCmdShort(char * Label) {
  char * aLabel = new char[strlen(Label)+2];
  aLabel[0] = '/';
  memcpy(&aLabel[1],Label,strlen(Label)+1);
  int i = 1;
  while ((i < getCmdCount()) && (strcmp(getCmdParam(i),aLabel) != 0)) i++;
  if (strcmp(getCmdParam(i),aLabel) == 0) {
    delete[] aLabel;
    return getCmdParam(i+1);
  }
  delete[] aLabel;
  return NULL;
}

bool SystemDefault_c::hasCmdShort(char * Label) {
  char * aLabel = new char[strlen(Label)+2];
  aLabel[0] = '/';
  memcpy(&aLabel[1],Label,strlen(Label)+1);
  int i = 1;
  while ((i < getCmdCount()) && (strcmp(getCmdParam(i),aLabel) != 0)) i++;
  if (strcmp(getCmdParam(i),aLabel) == 0) {
    delete[] aLabel;
    return true;
  }
  return false;
}
