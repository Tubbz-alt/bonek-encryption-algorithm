#ifndef __FEISTEL_H
#define __FEISTEL_H

#include "block.h"
#include "keygen.h"

struct Feistel {
  Feistel();
  Block encyprt(Block, byte*);
  Block decrypt(Block, byte*);
  
  Keygen keygen;
};

Feistel::Feistel() {
  
}

Block Feistel::encyprt(Block plain, byte* key) {
  
}

Block Feistel::decrypt(Block plain, byte* key) {
  
}


#endif