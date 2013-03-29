#ifndef FILE_H
#define FILE_H

#if run
#include <windows.h>
#endif

class file_c
{
    public:
        file_c();
        virtual ~file_c();
        bool OpenReadFile(char * aName);
        bool OpenWriteFile(char * aName);
        int CloseFile();
        int readFile(char * buffer,int bufferSize);
        int WriteBuffer(char * buffer, int size);
    protected:
    private:
      HANDLE _file;
      bool DirectoryExists(const char * aDir);
      bool CheckDir(char * aName);
};

#endif // FILE_H
