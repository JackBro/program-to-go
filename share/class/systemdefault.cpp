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
  printf("%s %d\n",CmdLine, getCmdCount());
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
