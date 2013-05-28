/*! \file share/class/registry.cpp
 *  \brief Kapsellung der Registryfunktionen
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#include "registry.h"

typedef LONG WINAPI (*_RegOpenKeyEx) (HKEY,LPCSTR,DWORD,REGSAM,PHKEY); /**< Definition der Funktion RegOpenKeyEx */
typedef LONG WINAPI (*_RegQueryValueEx) (HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD); /**< Definition der Funktion RegQueryValueEx */
typedef LONG WINAPI (*_RegSetValueEx) (HKEY,LPCSTR,DWORD,DWORD,const BYTE*,DWORD); /**< Definition der Funktion RegSetValueEx */
typedef LONG WINAPI (*_RegDeleteValue) (HKEY,LPCSTR);  /**< Definition der Funktion RegDeleteValue */
typedef LONG WINAPI (*_RegCloseKey) (HKEY);  /**< Definition der Funktion RegCloseEx */

HINSTANCE lib = 0; /**< Speichert die Instance der geladenen Bibliothek */
_RegOpenKeyEx __RegOpenKeyEx = NULL; /**< Speichert die Addrsse von RegOpenKeyEx */
_RegQueryValueEx __RegQueryValueEx = NULL; /**< Speichert die Addrsse von RegQueryValueEx */
_RegSetValueEx __RegSetValueEx = NULL; /**< Speichert die Addrsse von RegSetValueEx */
_RegDeleteValue __RegDeleteValue = NULL; /**< Speichert die Addrsse von RegDeleteValue */
_RegCloseKey __RegCloseKey = NULL; /**< Speichert die Addrsse von RegCloseKey */

/** \brief Initialiesiert die Klasse und lädt bei Bedarf die Bibliothek
 */
c_registry::c_registry()
{
   If (lib==0) lib = LoadLibrary("ADVAPI32.DLL");
}

/** \brief Schließt die Klasse
 */
c_registry::~c_registry()
{
}

/** \brief Öffnet einen Registry Key
 *
 * \param aKey HKEY Hauptschlüssel
 * \param sKey char* Pfad des Schlüssels
 * \return int Ergebnis der Windowsfunktion RegOpenKeyEx
 *
 */
int c_registry::OpenKey(HKEY aKey, char * sKey) {
  if (__RegOpenKeyEx == NULL) {
    __RegOpenKeyEx = (_RegOpenKeyEx) GetProcAddress (lib, "RegOpenKeyExA") ;
  }
  return __RegOpenKeyEx(aKey,sKey,NULL,KEY_ALL_ACCESS,&Key);
}

/** \brief Fragt einen Registry Wert ab
 *
 * \param Value char* Name des Wertes
 * \param data char* Speicherplatz für das Ergebnis
 * \param Size DWORD* Größe des Speicherplatzes
 * \return int Bei Erfolg 0
 * \return int Bei Fehler 1
 *
 */
int c_registry::QueryValue(char * Value, char * data, DWORD * Size) {
  if (__RegQueryValueEx == NULL) {
    __RegQueryValueEx = (_RegQueryValueEx) GetProcAddress (lib, "RegQueryValueExA") ;
  }
  if (__RegQueryValueEx(Key,Value,NULL,NULL,(LPBYTE)data,Size) == ERROR_SUCCESS) { return 0;};
  return 1;
}

/** \brief Setzt einen Registrywert
 *
 * \param Value char* Name des Wertes
 * \param data char* Wert
 * \return int immmer 0
 *
 */
int c_registry::SetValue(char * Value,char * data) {
  if (__RegSetValueEx == NULL) {
    __RegSetValueEx = (_RegSetValueEx) GetProcAddress (lib, "RegSetValueExA") ;
  }
  __RegSetValueEx(Key,Value,NULL,REG_SZ,(LPBYTE)data,strlen(data)+1);
  return 0;
}

/** \brief Löscht einen Registrywert
 *
 * \param Value char* Name des Wertes
 * \return int immer 0
 *
 */
int c_registry::DeleteValue(char * Value) {
  if (__RegDeleteValue == NULL) {
    __RegDeleteValue = (_RegDeleteValue) GetProcAddress (lib, "RegDeleteValueA") ;
  }
  __RegDeleteValue(Key,Value);
  return 0;
}

/** \brief Schließ den zuvor geöffneten Schlüssel
 *
 * \return int immer 0
 *
 */
int c_registry::CloseKey() {
  if (__RegCloseKey == NULL) {
    __RegCloseKey = (_RegCloseKey) GetProcAddress (lib, "RegCloseKey") ;
  }
  __RegCloseKey(Key);
  return 0;
}
