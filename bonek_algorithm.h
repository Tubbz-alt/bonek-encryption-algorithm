#ifndef __BONEK_
#define __BONEK_

#include "block.h"
#include "cbc.h"
#include "feistel.h"
#include "keygen.h"

using namespace std;

struct Bonek {
  Bonek();
  vector<Block> encyprt(vector<Block>, Block);
  vector<Block> decrypt(vector<Block>, Block);
  
  Keygen keygen;
};

Bonek::Bonek() {
  
}

vector<Block> Bonek::encyprt(vector<Block> plain, Block key) {
  Block ori_key = key;
  Keygen keygen;
  Cbc cbc;
  Feistel feistel;
  for(int i = 0; i < plain.size(); i++) {
    plain[i] = plain[i] ^ ori_key;
  }
  for(int round = 0; round < 10; round++) {
    key.bit = keygen.nextByteKey(key.bit);
    plain = cbc.encrypt(plain, key.bit);
    for(int f = 0; f < 2; f++) {
      key.bit = keygen.nextByteKey(key.bit);
      Block keyfi(4), keyse(4);
      tie(keyfi, keyse) = key.split();
      for(int i = 0; i < plain.size(); i++) {
        plain[i] = feistel.encrypt(plain[i], keyfi.bit);
        plain[i] = feistel.encrypt(plain[i], keyse.bit);
      }
    }
  }
  for(int i = 0; i < plain.size(); i++) {
    plain[i] = plain[i] ^ ori_key;
  }
  return plain;
}

vector<Block> Bonek::decrypt(vector<Block> cipher, Block key) {
  Block ori_key = key;
  Keygen keygen;
  Cbc cbc;
  Feistel feistel;
  for(int i = 0; i < 31; i++) key.bit = keygen.nextByteKey(key.bit);
  for(int i = 0; i < cipher.size(); i++) {
    cipher[i] = cipher[i] ^ ori_key;
  }
  for(int round = 0; round < 10; round++) {
    for(int f = 0; f < 2; f++) {
      key.bit = keygen.prevByteKey(key.bit);
      Block keyfi(4), keyse(4);
      tie(keyfi, keyse) = key.split();
      for(int i = 0; i < cipher.size(); i++) {
        cipher[i] = feistel.decrypt(cipher[i], keyfi.bit);
        cipher[i] = feistel.decrypt(cipher[i], keyse.bit);
      }
    }
    key.bit = keygen.prevByteKey(key.bit);
    cipher = cbc.decrypt(cipher, key.bit);
  }
  for(int i = 0; i < cipher.size(); i++) {
    cipher[i] = cipher[i] ^ ori_key;
  }
  return cipher;
}  

#endif