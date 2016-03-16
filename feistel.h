#ifndef __FEISTEL_H
#define __FEISTEL_H

#include "block.h"
#include "keygen.h"

struct Feistel {
  Feistel();
  Block encrypt(Block, byte*);
  Block decrypt(Block, byte*);
  
  Keygen keygen;
};

Feistel::Feistel() {
  
}

Block Feistel::encrypt(Block plain, byte* key) {
  Block fi(4), se(4), newfi(4), newse(4);
  tie(fi, se) = plain.split();
  newfi = se;
  newse = se.f_encrypt(Block(4, key)) ^ fi;
  Block ret(8);
  ret.combine(newfi, newse);
  return ret;
}

Block Feistel::decrypt(Block cipher, byte* key) {
  Block fi(4), se(4), newfi(4), newse(4);
  tie(fi, se) = cipher.split();
  newse = fi;
  newfi = fi.f_encrypt(Block(4, key)) ^ se;
  Block ret(8);
  ret.combine(newfi, newse);
  return ret;
}


#endif