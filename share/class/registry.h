/*! \file share/class/registry.cpp
 *  \brief Kapsellung der Registryfunktionen
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef REGISTRY_H
#define REGISTRY_H

#include <windows.h>

/** \brief Klasse zum Kapseln der Regstryfunktionen
 */
class c_registry
{
  public:
    c_registry();
    virtual ~c_registry();
    int OpenKey(HKEY aKey, char * sKey);
    int QueryValue(char * Value, char * data, DWORD * Size);
    int SetValue(char * Value, char * data);
    int DeleteValue(char * Value);
    int CloseKey();
  protected:
    HKEY Key; /**< Handle des offen Schluessels */
  private:
};

#endif // REGISTRY_H
