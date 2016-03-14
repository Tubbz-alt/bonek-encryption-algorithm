#ifndef __CBC_H
#define __CBC_H

#include "keygen.h"

struct Cbc {
  Cbc();
  void encyprt(byte*, byte*);
  void decrypt(byte*, byte*);
  
  Keygen keygen;
};

Cbc::Cbc() {
  
}

void Cbc::encyprt(byte* plain, byte* key) {
  
}

void Cbc::decrypt(byte* plain, byte* key) {
  
}

#endif