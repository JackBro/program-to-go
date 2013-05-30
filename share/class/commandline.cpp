/*! \file share/class/commandline.cpp
 *  \brief Klasse für Verarbeitung der Commandline
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#include "commandline.h"

#include <stdio.h>
#include <windows.h>

/** \brief Initialiersiert die Commandline und lädt die Commandline
 */
c_commandline::c_commandline()
{
  int len = strlen(GetCommandLine());
  cmdline = new char[len+1];
  memcpy(cmdline,GetCommandLine(),len+1);
  cmdcount = -1;
}

/** \brief Gibt die Commandline wieder frei
 */
c_commandline::~c_commandline()
{
  delete[] cmdline;
}

/** \brief Gib die Anzahl der Element zurueck, bei erstenmal wird die Anzahl ermittelt
 *
 * \return int Anzahl der Elemente
 *
 */
int c_commandline::cmdGetCount() {
  if (cmdcount == -1) {
    int c = 0;
    char * pos = cmdline;
    bool quotes;
    while (strlen(pos)>0) {
      quotes = hasQuotes(pos);
      if (quotes) {
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
    cmdcount = c;
  }
  return cmdcount;
}

/** \brief prüft ob der nächste Parameter mit Anfuerungszeichen beginnt
 *
 * \param ch char* Start des Parameters
 * \return bool true wenn das erste Zeichen ein Anfuerungszeichen ist
 * \return bool false wenn das erste Zeichen kein Anfuerungszeichen ist
 *
 */
bool c_commandline::hasQuotes(char * ch)
{
  return ch[0] == '\"';
}

/** \brief Ermittelt die Start der Parameter
 *
 * \return char* Gibt die Parameterliste zurück
 *
 */
char * c_commandline::cmdGetParams()
{
  if (cmdGetCount() > 1) {
    char * pos = cmdline;
    bool quotes = hasQuotes(pos);
    if (quotes) {
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
    return pos;
  } else return NULL;
}

/** \brief Ergibt einen Paramter zurueck
 *
 * \param i int Nummer des gewünschten Parameters
 * \return char* das Element oder NULL wenn der Parameter nicht existiert
 *
 */
char * c_commandline::cmdGetParam(int i)
{
    char * pos = cmdline;
  char * start;
  if (i<cmdGetCount()) {
    int c = 0;
    start = pos;
    while ((c < i) && (strlen(pos)>0)) {
      bool useFuss = false;
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
      start = pos;
    }
  }
  if (start != NULL) {
    char * ende = start;
    bool useFuss = ende[0] == '\"';
    if (useFuss) {
      ende = ende + 1;
      while ((strlen(ende) > 0) && (ende[0] != '\"')) {
        ende = ende + 1;
      }
      ende = ende + 1;
    } else {
      while ((strlen(ende) > 0) && (ende[0] != ' ')) {
        ende = ende + 1;
      }
    }
    int len = strlen(start)-strlen(ende);
    char * ret = new char[len+1];
    useFuss = start[0] == '\"';
    if (useFuss) {
      memcpy(ret,start+1,len-1);
      ret[len-2] = 0;
    } else {
      memcpy(ret,start,len);
      ret[len] = 0;
    }
    return ret;
  }
  return NULL;
}

/** \brief gibt den Wert eines Parameters zurueck, kurze Parameter begint mit /
 *
 * \param Label char* Parameter
 * \return char* Wert des Paramters oder NULL wenn kein Wert vorliegt
 *
 */
char * c_commandline::cmdGetShort(char * Label)
{
    char * aLabel = new char[strlen(Label)+2];
  aLabel[0] = '/';
  memcpy(&aLabel[1],Label,strlen(Label)+1);
  int i = 1;
  while ((i < cmdGetCount()) && (strcmp(cmdGetParam(i),aLabel) != 0)) i++;
  if ((i < cmdGetCount()) &&(strcmp(cmdGetParam(i),aLabel) == 0)) {
    delete[] aLabel;
    return cmdGetParam(i+1);
  }
  delete[] aLabel;
  return NULL;
}

/** \brief Prüft ob ein kurzer Parameter existiert, kurze Parameter begint mit /
 *
 * \param Label char* gefragter Parameter
 * \return bool true wenn der Parameter existiert
 *
 */
bool c_commandline::cmdHasShort(char * Label)
{
  char * aLabel = new char[strlen(Label)+2];
  aLabel[0] = '/';
  memcpy(&aLabel[1],Label,strlen(Label)+1);
  int i = 1;
  while ((i < cmdGetCount()) && (strcmp(cmdGetParam(i),aLabel) != 0)) i++;
  if (strcmp(cmdGetParam(i),aLabel) == 0) {
    delete[] aLabel;
    return true;
  }
  return false;
}
