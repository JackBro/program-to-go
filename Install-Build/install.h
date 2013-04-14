#ifndef INSTALL_H_INCLUDED
#define INSTALL_H_INCLUDED

typedef struct {
  DWORD id;
  DWORD aSize;
} install_rec;

#define install_lang    0x1234
#define install_program 0x1235

#endif
