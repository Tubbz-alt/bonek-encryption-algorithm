#ifndef __CBC_H
#define __CBC_H

#include <vector>

#include "keygen.h"

using namespace std;

struct Cbc {
  Cbc();
  vector<Block> encrypt(vector<Block>, byte*);
  vector<Block> decrypt(vector<Block>, byte*);
  
  Keygen keygen;
};

Cbc::Cbc() {
  
}

vector<Block> Cbc::encrypt(vector<Block> plain, byte* k) {
  Block K(8, k);
  byte* key = K.bit;
  vector<Block> cip;
  Keygen keygen;
  byte* pre = key;
  for(int i = 0; i < plain.size(); i++) {
    key = keygen.nextByteKey(key);
    plain[i] = plain[i] ^ Block(8, pre);
    cip.push_back(plain[i].e_encrypt(Block(8, key)));
    pre = cip.back().bit;
  }
  return cip;
}

vector<Block> Cbc::decrypt(vector<Block> cipher, byte* k) {
  Block K(8, k);
  byte* key = K.bit;
  vector<Block> pres, keys, plain;
  Keygen keygen;
  pres.push_back(Block(8, key));
  for(int i = 0; i + 1 < cipher.size(); i++) {
    pres.push_back(cipher[i]);
  }
  for(int i = 0; i < cipher.size(); i++) {
    key = keygen.nextByteKey(key);
    keys.push_back(Block(8, key));
  }
  for(int i = 0; i < cipher.size(); i++) {
    Block tmp = cipher[i].e_decrypt(keys[i]);
    plain.push_back(tmp ^ pres[i]);
  }
  return plain;
}

#endif