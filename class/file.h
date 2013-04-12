#ifndef FILE_H
#define FILE_H

#include <windows.h>

class file_c
{
    public:
        file_c();
        virtual ~file_c();
        bool OpenReadFile(char * aName);
        bool OpenWriteFile(char * aName);
        bool OpenReadWriteFile(char * aName);
        int CloseFile();
        int readFile(char * buffer,int bufferSize);
        int WriteBuffer(char * buffer, int size);
        int seek(DWORD aSize, DWORD aPos);
    protected:
    private:
      HANDLE _file;
      bool DirectoryExists(const char * aDir);
      bool CheckDir(char * aName);
};

#endif // FILE_H
