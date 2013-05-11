/*! \file _comdlg32.cpp
 *  \brief Die Klassen zum Zugriff auf "commdlg32"
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#include "_comdlg32.h"

/** \todo both dialog with one parentclass */

/////////////////////////////////////////////////////
// Start Definitionen aus commdlg.h                //
/////////////////////////////////////////////////////

#ifndef NODOXYGEN

#define OFN_ALLOWMULTISELECT 512
#define OFN_CREATEPROMPT 0x2000
#define OFN_ENABLEHOOK 32
#define OFN_ENABLESIZING 0x800000
#define OFN_ENABLETEMPLATE 64
#define OFN_ENABLETEMPLATEHANDLE 128
#define OFN_EXPLORER 0x80000
#define OFN_EXTENSIONDIFFERENT 0x400
#define OFN_FILEMUSTEXIST 0x1000
#define OFN_HIDEREADONLY 4
#define OFN_LONGNAMES 0x200000
#define OFN_NOCHANGEDIR 8
#define OFN_NODEREFERENCELINKS 0x100000
#define OFN_NOLONGNAMES 0x40000
#define OFN_NONETWORKBUTTON 0x20000
#define OFN_NOREADONLYRETURN 0x8000
#define OFN_NOTESTFILECREATE 0x10000
#define OFN_NOVALIDATE 256
#define OFN_OVERWRITEPROMPT 2
#define OFN_PATHMUSTEXIST 0x800
#define OFN_READONLY 1
#define OFN_SHAREAWARE 0x4000
#define OFN_SHOWHELP 16
#define OFN_SHAREFALLTHROUGH 2
#define OFN_SHARENOWARN 1
#define OFN_SHAREWARN 0
#define OFN_NODEREFERENCELINKS 0x100000
#if (_WIN32_WINNT >= 0x0500)
#define OFN_DONTADDTORECENT 0x02000000
#endif


typedef struct _tagOFNA {
	DWORD lStructSize;
	HWND hwndOwner;
	HINSTANCE hInstance;
	LPCSTR lpstrFilter;
	LPSTR lpstrCustomFilter;
	DWORD nMaxCustFilter;
	DWORD nFilterIndex;
	LPSTR lpstrFile;
	DWORD nMaxFile;
	LPSTR lpstrFileTitle;
	DWORD nMaxFileTitle;
	LPCSTR lpstrInitialDir;
	LPCSTR lpstrTitle;
	DWORD Flags;
	WORD nFileOffset;
	WORD nFileExtension;
	LPCSTR lpstrDefExt;
	DWORD lCustData;
	LPOFNHOOKPROC lpfnHook;
	LPCSTR lpTemplateName;
#if (_WIN32_WINNT >= 0x0500)
	void * pvReserved;
	DWORD dwReserved;
	DWORD FlagsEx;
#endif /* (_WIN32_WINNT >= 0x0500) */
} _OPENFILENAMEA,*_LPOPENFILENAMEA;

typedef BOOL WINAPI (*_GetOpenFileNameA) (_LPOPENFILENAMEA);
typedef BOOL WINAPI (*_GetSaveFileNameA) (_LPOPENFILENAMEA);
#ifdef debug
typedef DWORD WINAPI (*_CommDlgExtendedError) (void);
#endif
#define _GetOpenFileName _GetOpenFileNameA
#define _GetSaveFileName _GetSaveFileNameA
#endif // NODOXYGEN

HINSTANCE lib = NULL; /**< Speichert die Instance vom commdlg */
_GetOpenFileName  __GetOpenFileName = NULL; /**< Speichert die Funktion GetOpenFileName */
_GetSaveFileName  __GetSaveFileName = NULL; /**< Speichert die Funktion GetSaveFileName */
#ifdef debug
_CommDlgExtendedError  __CommDlgExtendedError = NULL; /**< Speichert die Funktion CommDlgExtendedError */
#endif

/////////////////////////////////////////////////////
// Stop Definitionen aus commdlg.h                 //
/////////////////////////////////////////////////////

/**
 *  Intialiesiert bei Bedarf die Biliothek, und setzt Variablen auf NULL
 */
c_getopenfilename::c_getopenfilename()
{
  if (lib == NULL) {
    lib = LoadLibrary ("COMDLG32.dll") ;
  }
  if (__GetOpenFileName == NULL) {
    __GetOpenFileName = (_GetOpenFileName) GetProcAddress (lib, "GetOpenFileNameA") ;
  }
#ifdef debug
  if (__CommDlgExtendedError == NULL) {
    __CommDlgExtendedError = (_CommDlgExtendedError) GetProcAddress (lib, "CommDlgExtendedError") ;
  }
#endif
  fname = NULL;
  filter = NULL;
  pfad = NULL;
  hWnd = 0;
}

/**
 *  Gibt bei Bedarf die Variablen wieder frei
 */
c_getopenfilename::~c_getopenfilename()
{
  if (filter != NULL) delete[] filter;
  if (pfad != NULL) delete[] pfad;
  if (fname != NULL) delete[] fname;
}

/**
 *  Ruft den Dialog GetOpenFileName auf
 *  die ausgewaelte Datei wird in fname gespeichert
 *  \return Gibt die ausgewaelte Datei zurueck
 */
char * c_getopenfilename::get() {
  if (fname == NULL) {
    fname = new char[MAX_PATH];
    fname[0] = 0;
  }
  _OPENFILENAMEA ofn;
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = hWnd;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fname;
  ofn.lpstrInitialDir = pfad;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  if(!__GetOpenFileName(&ofn)) {
#ifdef debug
    printf ("GetOpenFileName Error: %d\n",__CommDlgExtendedError());
#endif
  }
  return fname;
}

/**
 *  Setzt den Filter
 *  im Unterschied zu Windows wird ";" anstelle von 0 zum trennen benutzt,
 *  am Ende muessen 2 ";" stehen
 *  \param aFilter ein String der die Filterdefinition enthaelt
 *  \return gibt immer 0 zurueck
 */
int c_getopenfilename::setFilter(char * aFilter) {
  if (filter != NULL) delete[] filter;
  filter = new char[strlen(aFilter)+1];
  memcpy(filter, aFilter, strlen(aFilter)+1);
  for (int i=strlen(filter); i>0; i--) {
    if (filter[i] == ';') filter[i] = 0;
  }
  return 0;
}

/**
 *  Setzt den Startordner
 *  \param aPfad Orner der zu begin geoeffnet werden soll
 *  \return gibt immer 0 zurueck
 */
int c_getopenfilename::setPfad(char * aPfad) {
  if (pfad != NULL) delete[] pfad;
  pfad = new char[strlen(aPfad)+1];
  memcpy(pfad, aPfad, strlen(aPfad)+1);
  return 0;
}

/**
 *  Setzt das Elternfenster
 *  \param ahWnd Elternfenster
 *  \return gibt immer 0 zurueck
 */
int c_getopenfilename::setHWnd(HWND ahWnd) {
  hWnd = ahWnd;
  return 0;
}

/////////////////////////////////////////////////////

/**
 *  Intialiesiert bei Bedarf die Biliothek, und setzt Variablen auf NULL
 */
c_getsavefilename::c_getsavefilename()
{
  if (lib == NULL) {
    lib = LoadLibrary ("COMDLG32.dll") ;
  }
  if (__GetSaveFileName == NULL) {
    __GetSaveFileName = (_GetSaveFileName) GetProcAddress (lib, "GetSaveFileNameA") ;
  }
#ifdef debug
  if (__CommDlgExtendedError == NULL) {
    __CommDlgExtendedError = (_CommDlgExtendedError) GetProcAddress (lib, "CommDlgExtendedError") ;
  }
#endif
  fname = NULL;
  filter = NULL;
  pfad = NULL;
  hWnd = 0;
}

/**
 *  Gibt bei Bedarf die Variablen wieder frei
 */
c_getsavefilename::~c_getsavefilename()
{
  if (filter != NULL) delete[] filter;
  if (pfad != NULL) delete[] pfad;
  if (fname != NULL) delete[] fname;
}

/**
 *  Ruft den Dialog GetSaveFileName auf
 *  die ausgewaelte Datei wird in fname gespeichert
 *  \return Gibt die ausgewaelte Datei zurueck
 */
char * c_getsavefilename::get() {
  if (fname == NULL) {
    fname = new char[MAX_PATH];
    fname[0] = 0;
  }
  _OPENFILENAMEA ofn;
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = hWnd;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fname;
  ofn.lpstrInitialDir = pfad;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  if(!__GetSaveFileName(&ofn)) {
#ifdef debug
    printf ("GetOpenFileName Error: %d\n",__CommDlgExtendedError());
#endif
  }
  return fname;
}

/**
 *  Setzt den Filter
 *  im Unterschied zu Windows wird ";" anstelle von 0 zum trennen benutzt,
 *  am Ende muessen 2 ";" stehen
 *  \param aFilter ein String der die Filterdefinition enthaelt
 *  \return gibt immer 0 zurueck
 */
int c_getsavefilename::setFilter(char * aFilter) {
  if (filter != NULL) delete[] filter;
  filter = new char[strlen(aFilter)+1];
  memcpy(filter, aFilter, strlen(aFilter)+1);
  for (int i=strlen(filter); i>0; i--) {
    if (filter[i] == ';') filter[i] = 0;
  }
  return 0;
}

/**
 *  Setzt den Startordner
 *  \param aPfad Orner der zu begin geoeffnet werden soll
 *  \return gibt immer 0 zurueck
 */
int c_getsavefilename::setPfad(char * aPfad) {
  if (pfad != NULL) delete[] pfad;
  pfad = new char[strlen(aPfad)+1];
  memcpy(pfad, aPfad, strlen(aPfad)+1);
  return 0;
}

/**
 *  Setzt das Elternfenster
 *  \param ahWnd Elternfenster
 *  \return gibt immer 0 zurueck
 */
int c_getsavefilename::setHWnd(HWND ahWnd) {
  hWnd = ahWnd;
  return 0;
}
