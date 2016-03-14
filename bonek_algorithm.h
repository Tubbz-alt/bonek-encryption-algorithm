#ifndef __BONEK_
#define __BONEK_

#include "keygen.h"

struct Bonek {
  Bonek();
  byte* encyprt(byte*, byte*);
  byte* decrypt(byte*, byte*);
  
  Keygen keygen;
};

Bonek::Bonek() {
  
}

void Bonek::encyprt(byte* plain, byte* key) {
  
}

void Bonek::decrypt(byte* cipher, byte* key) {

}  

#endif