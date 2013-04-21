#include "icon.h";

#include <stdio.h>
#include <windows.h>

int setIcon(char * sourcePrg, char * destPrg) {
  HMODULE hSrcExe, hDestExe;
  HRSRC hRes;         // handle/ptr. to res. info. in hExe
  HRSRC hResLoad;     // handle to loaded resource
  char *lpResLock;    // pointer to resource data
  HANDLE hUpdateRes;  // update resource handle
  BOOL result;
  int iLoop;
  char  str[10];

//Load the source exe from where we need the icon
  hSrcExe = LoadLibrary(sourcePrg);
  if(hSrcExe == NULL) return 1;
  // Locate the ICON resource in the .EXE file.
  for(iLoop = 1;;iLoop++) {
    snprintf(str,10,"#%d",iLoop);
    hRes = FindResource(hSrcExe, str, RT_ICON);
    if (hRes == NULL) continue ;
    else { if(iLoop == 600) return 1;
      else break;
    }
  }
// Load the ICON into global memory.
  hResLoad = (HRSRC)LoadResource(hSrcExe, hRes);
  if (hResLoad == NULL) return 1;
// Lock the ICON into global memory.
  lpResLock = (char*)LockResource(hResLoad);
  if (lpResLock == NULL) return 1 ;
  hDestExe = LoadLibrary(destPrg);
  if(hDestExe == NULL) return 1;
// Locate the ICON resource in the .EXE file.
  for(iLoop = 1;;iLoop++) {
    snprintf(str,10,"#%d",iLoop);
    if (FindResource(hDestExe, str, RT_ICON) == NULL)
        continue ;
    else if(iLoop == 10)
        break;
    else
        break;
  }
  FreeLibrary(hDestExe);
  // Open the file to which you want to add the ICON resource.
  hUpdateRes = BeginUpdateResource(destPrg, FALSE);
  if (hUpdateRes == NULL) return 2;
  result = UpdateResource(hUpdateRes,       // update resource handle
    RT_ICON,                   // change dialog box RT_STRING
    MAKEINTRESOURCE(1),
    MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),  // neutral language
    lpResLock,                   // ptr to resource info
    SizeofResource(hSrcExe, hRes)); // size of resource info.
  if (result == FALSE) return 2;
// Write changes then close it.
  if (!EndUpdateResource(hUpdateRes, FALSE)) {return 2; }
  return 0;
}
