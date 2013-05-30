/*! \file share/class/commandline.h
 *  \brief Klasse für Verarbeitung der Commandline
 *
 * \author Frank Holler
 * \date 2013.05
 * \copyright GNU Public License.
 */
#ifndef C_COMMANDLINE
#define C_COMMANDLINE

class c_commandline
{
    public:
      c_commandline();
      virtual ~c_commandline();
      int cmdGetCount();
      char * cmdGetParams();
      char * cmdGetParam(int i);
      char * cmdGetShort(char * Label);
      bool cmdHasShort(char * Label);
    protected:
      char * cmdline; /**< Hält die Commandline als String */
      int cmdcount; /**< Anzahl der Elemente der Commandline */
    private:
      bool hasQuotes(char * ch);
};

#endif // C_COMMANDLINE
