#ifndef __CBC_H
#define __CBC_H

#include <vector>

#include "keygen.h"

using namespace std;

struct Cbc {
  Cbc();
  vector<Block> encyprt(vector<Block>, byte*);
  vector<Block> decrypt(vector<Block>, byte*);
  
  Keygen keygen;
};

Cbc::Cbc() {
  
}

vector<Block> Cbc::encyprt(vector<Block> plain, byte* key) {
  vector<Block> cip;
  Keygen keygen;
  byte* pre = key;
  key = keygen.nextByteKey(key);
  for(int i = 0; i < plain.size(); i++) {
    plain[i] = plain[i] ^ Block(8, pre);
    cip.push_back(plain[i].e_encrypt(Block(8, key)));
    pre = cip.back().bit;
  }
  return cip;
}

vector<Block> Cbc::decrypt(vector<Block> cipher, byte* key) {
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
    cipher[i].e_decrypt(keys[i]);
    plain.push_back(cipher[i] ^ pres[i]);
  }
  return plain;
}

#endif