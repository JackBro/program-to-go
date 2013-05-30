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
}

SystemDefault_c::~SystemDefault_c()
{
    //dtor
}

bool SystemDefault_c::DriveRemovable() {
  return (DRIVE_CDROM == DriveMode) || (DRIVE_REMOVABLE == DriveMode);
}
