#ifndef LANGUAGE_H
#define LANGUAGE_H

#if run
#undef WINVER
#define WINVER 0x502
#include <windows.h>
#endif

#include "../../share/class/systemdefault.h"
#include "../../share/class/collection.h"
#include "../../share/class/languagefile.h"
//#include "../../share/class/initcontrols.h"
//#include "../../share/class/dropdownlist.h"
//#include "setupfile.h"

class language_c : public collection_c {
    public:
      language_c(char * setupLang, SystemDefault_c * SystemDefault);
      virtual ~language_c();
      int LoadLanguageFile(char * aFile);
//      int allLangToCombo(dropdownlist_c * list);
      char * getLang(int id);
      char * setCurrentByLabel(char * aLabel);
      char * getLangName(int id);
//      int setSetup(setupfile_c * aSetup);
//      int setControlText(initcontrols_c * control,int id);
      char * getCurLang();
      char * getLangText(int id);
      int current;
    protected:
      char * langDir;
    private:
      int getLangIDMain(int lang);
      int getLangID(int lang);
      int hexToInt(const char * hex);
//      setupfile_c * setup;
};


#endif // LANGUAGE_H
