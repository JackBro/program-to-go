#include "systemdefault.h"

#ifdef debug
#include <stdio.h>
#endif

SystemDefault_c::SystemDefault_c()
{
  GetModuleFileName(NULL,ExeFile,MAX_PATH);
#ifdef debug
//  printf("Exefile %s\n",ExeFile);
#endif
  char slash[2] = "\\";
  strcpy(ExePath,ExeFile);
  while ((strlen(ExePath) > 0) && (strcmp(&ExePath[strlen(ExePath)-1],&slash[0]) != 0)) {
    ExePath[strlen(ExePath)-1] = 0;
  }
#ifdef debug
//  printf("ExePath %s\n",ExePath);
#endif
  memcpy(Drive,ExeFile,3);
  Drive[3] = 0;
<<<<<<< HEAD
  GetCurrentDirectory(MAX_PATH,PrgPath);
  PrgPath[strlen(PrgPath)+1] = 0;
  PrgPath[strlen(PrgPath)] = '\\';
=======
>>>>>>> 3c701b4182657a77d3f4c867a8d13e31aa099dc4
#ifdef debug
//  printf("ExePath %s\n",Drive);
#endif
  DriveMode = GetDriveType(Drive);
#ifdef debug
//  printf("%d\n",DriveMode);
#endif
  GetTempPath(MAX_PATH, TempPath);
  _OSVERSIONINFOA Version;
  Version.dwOSVersionInfoSize = sizeof(_OSVERSIONINFOA);
  GetVersionEx(&Version);
  HiVersion = Version.dwMajorVersion;
  LoVersion = Version.dwMinorVersion;
#ifdef debug
//  printf("%d %d\n",HiVersion,LoVersion);
#endif
}

SystemDefault_c::~SystemDefault_c()
{
    //dtor
}

bool SystemDefault_c::DriveRemovable() {
  return (DRIVE_CDROM == DriveMode) || (DRIVE_REMOVABLE == DriveMode);
}
