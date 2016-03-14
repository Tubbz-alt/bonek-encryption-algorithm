#ifndef __FEISTEL_H
#define __FEISTEL_H

#include "keygen.h"

struct Feistel {
  Feistel();
  void encyprt(byte*, byte*);
  void decrypt(byte*, byte*);
  
  Keygen keygen;
};

Feistel::Feistel() {
  
}

void Feistel::encyprt(byte* plain, byte* key) {
  
}

void Feistel::decrypt(byte* plain, byte* key) {
  
}


#endif