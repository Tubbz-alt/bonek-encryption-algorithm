#ifndef __CBC_H
#define __CBC_H

#include "keygen.h"

struct Cbc {
  Cbc();
  Block* encyprt(Block*, byte*);
  Block* decrypt(Block*, byte*);
  
  Keygen keygen;
};

Cbc::Cbc() {
  
}

Block* Cbc::encyprt(Block* plain, byte* key) {
  
}

Block* Cbc::decrypt(Block* plain, byte* key) {
  
}

#endif