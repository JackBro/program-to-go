/*! \file Make-Splash/class/setupfile.h
 *  \brief Die Hauptdatei vom Projekt "Make-Splash"
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef SETUPFILE_H
#define SETUPFILE_H

#include "..\..\libs\libxml2\tinyxml2.h"
#include "..\..\share\tools.h"

/** \brief Klasse zum Speichern der Grundeinstellungen
 */
class setupfile_c
{
    public:
        setupfile_c(const char * aPfad, const char * aFile);
        virtual ~setupfile_c();
        char * getLang();
        int setLang(const char * aLang);
        int checkSave();
        bool changed; /**< Speichert den Zustand, ob Einstellungen veraendert wurden */
    protected:
    private:
      char * fName; /**< Speichert den Dateinanmen der Konfigurationsdatei */
      tinyxml2::XMLDocument * xml; /**< Haelt das XML-Dokument */
};

#endif // SETUPFILE_H
