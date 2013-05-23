/*! \file Make-Splash/init.cpp
 *  \brief Initialiesiert das Hauptfenster
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */

#include "init.h"

HWND hwnd; /**< Speichert das Handle des Hauptfensters */

pages_c * pages;
controlcollections_c * controls;
setupfile_c * setup;
staticlabel_c * progresslabel;
edit_c * progname;
edit_c * progversion;
edit_c * progmessage;
progress_c * progressbar;
fileedit_c * leftpic;
fileedit_c * rightpic;
fileedits_c * savefile;
SystemDefault_c * SystemDefault;
menu_c * menu; /**< Speichert das Hauptmenu */
language_c * language;
languagebox_c * langlist; /**< Speicht die Box fuer die Sprachauswahl */

/** \brief Funktion fuer den Weiter Button
 *
 * \return immer 0
 */
int * nextButtonClicked() {
  pages->nextPage();
  if (pages->getPage() == 3) {
    runIt(hwnd ,0);
  }
  return 0;
}

/** \brief Funktion fuer den Zurueck Button
 *
 * \return immer 0
 */
int * prevButtonClicked() {
  pages->prevPage();
  return 0;
}

/** \brief Funktion fuer den Exit Button
 *
 * \return immer 0
 */
int * finishButtonClicked() {
  SendMessage(hwnd,WM_DESTROY,0,0);
  return 0;
}

/** \brief Funktion fuer die Aenderung der Sprache
 *
 * \return immer 0
 */
int * languageClicked() {
  language->setCurrentByLabel(langlist->getText());
  controls->setCurLanguage();
  setup->setLang(language->getCurLang());
  menu->setLanguage(language);
}

/** \brief Intialiesiert das Hauptfenster
 *
 * \param wnd Handle des Fensters
 * \return immer 0
 */
int init(HWND wnd) {
  hwnd = wnd;
  SystemDefault = new SystemDefault_c;
  setup = new setupfile_c(SystemDefault->PrgPath,"config\\config.xml");
  language = new language_c(setup->getLang(), SystemDefault);
  setup->setLang(language->getCurLang());
  controls = new controlcollections_c;
  controls->setLanguage(language);
  font_c * font = new font_c;
  font->setSizeName(10,"Tahoma");
  font->create();
  controls->setFont(font);
  pages = new pages_c;
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Language:", 1, 10, 10, 200, 24)));
  langlist = (languagebox_c*)pages->addControl(
    controls->addControl(
       new languagebox_c(hwnd, 10, 35, 370, 12)));
  langlist->onClick = languageClicked;

////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Programname:", 6, 10, 10, 200, 24)));
  progname = (edit_c*)pages->addControl(
    controls->addControl(
       new edit_c(hwnd, 10, 35, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Version:", 9, 10, 65, 200, 24)));
  progversion = (edit_c*)pages->addControl(
    controls->addControl(
       new edit_c(hwnd, 10, 90, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Message:", 10, 10, 120, 200, 24)));
  progmessage = (edit_c*)pages->addControl(
    controls->addControl(
       new edit_c(hwnd, 10, 145, 370, 24)));
////////////
  pages->newPage();
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Left picture :", 12, 10, 10, 200, 24)));
  leftpic = (fileedit_c*)pages->addControl(
    controls->addControl(
       new fileedit_c(hwnd, ICON_FILE, 13, 10, 35, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Right picture :", 16, 10, 65, 200, 24)));
  rightpic = (fileedit_c*)pages->addControl(
    controls->addControl(
       new fileedit_c(hwnd, ICON_FILE, 13, 10, 90, 370, 24)));
  pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Save As:", 17, 10, 120, 200, 24)));
  savefile = (fileedits_c*)pages->addControl(
    controls->addControl(
       new fileedits_c(hwnd, ICON_FILE, 13, 10, 145, 370, 24)));
////////////
  pages->newPage();
  progresslabel = (staticlabel_c*)pages->addControl(
    controls->addControl(
       new staticlabel_c(hwnd, "Progress", 10, 10, 10, 370, 65)));
  progressbar = (progress_c*)pages->addControl(
    controls->addControl(
      new progress_c(hwnd, 10, 80, 370, 24)));
////////////
  pages->setPrevButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Back", 2, 107, 237, 85, 24)));
  pages->prevButton->onClick = prevButtonClicked;
  pages->setNextButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Next", 3, 202, 237, 85, 24)));
  pages->nextButton->onClick = nextButtonClicked;
  pages->setCloseButton(
    (button_c*)controls->addControl(
      new button_c(hwnd, "Finish", 4, 297, 237, 85, 24)));
  pages->closeButton->onClick = finishButtonClicked;
////////////
  menu = new menu_c;
  menu_c * submenu = new menu_c;
  submenu->Append(MENU_LOAD, 22, "Load");
  submenu->Append(MENU_SAVE, 23, "Save");
  submenu->Append(MENU_SAVEAS, 24, "Save as");
  menu->AppendMenu(0, 21, "File", submenu);
  menu->setMenu(hwnd);
////////////
  langlist->setLangList();
  controls->setCurLanguage();
  menu->setLanguage(language);
////////////
  if (setup->changed) {
    pages->setPage(0);
  } else {
    pages->setPage(1);
  }
////////////
  SetTimer(hwnd, TIMER_START, 100, 0);
  return 0;
}

/** \brief 2. Teil der Initialiesierung (Commandline Auswertung)
 *
 * \param wnd HWND Handel des Fensters
 * \return immer 0
 *
 */
int init2(HWND wnd) {
  char * Pfad = SystemDefault->getCmdShort("l");
  if (Pfad != NULL) {
    LoadData(Pfad);
    delete[] Pfad;
  }
  if (SystemDefault->hasCmdShort("r")) {
    pages->setPage(3);
    runIt(wnd,0);
  }
  return 0;
}
