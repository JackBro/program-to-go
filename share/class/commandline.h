#ifndef C_COMMANDLINE
#define C_COMMANDLINE


class c_commandline
{
    public:
      c_commandline();
      virtual ~c_commandline();
      int cmdGetCount();
      char * cmdGetParams();
    protected:
      char * cmdline;
      int cmdcount;
    private:
      bool hasQuotes(char * ch);
};

#endif // C_COMMANDLINE
