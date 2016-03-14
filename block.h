#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <algorithm>

#include "global.h"
#include "keygen.h"

using namespace std;

/* Block is 128-bit, all constant defined in global.h */
struct Block {
  Block() : BIT_SIZE(8) {
    bit = new byte[BLOCK_SIZE];
    fill(bit, bit + BLOCK_SIZE, 0);
  }
  Block(int n) : BIT_SIZE(n) {
    bit = new byte[BLOCK_SIZE];
    fill(bit, bit + BLOCK_SIZE, 0);
  }
  Block(int n, byte* b) : BIT_SIZE(n) {
    bit = new byte[BLOCK_SIZE];
    for(int i = 0; i < BLOCK_SIZE; i++) {
      bit[i] = b[i];
    }
  }
  ~Block() {
    delete [] bit;
  }
  byte get(int i) {
    return bit[i];
  }
  void set(int i, byte b) {
    bit[i] = b;
  }
  void operator=(const Block&) const;
  Block operator+(const Block&) const;
  Block operator-(const Block&) const;
  Block operator^(const Block&) const;
  Block operator<<(int) const;
  Block operator>>(int) const;
  Block rotate();
  Block transpose();
  
  Block e_encrypt(Block);
  Block e_decrypt(Block);
  Block f_encrypt(Block);
  Block f_decyprt(Block);
  
  byte* bit = NULL;         // a container array, consist of byte/hex of Block
  int BIT_SIZE;             // 8 for byte, 4 for hex 
};

void Block::operator=(const Block& b) const {
  for(int i = 0; i < BLOCK_SIZE; i++) {
    bit[i] = b.bit[i];
  }
}

Block Block::operator+(const Block& b) const {
  Block ret(BIT_SIZE);
  for(int i = 0; i < BLOCK_SIZE; i++) {
    ret.bit[i] = (this->bit[i] + b.bit[i]) % (1 << BIT_SIZE);
  }
  return ret;
}

Block Block::operator-(const Block& b) const {
  Block ret(BIT_SIZE);
  for(int i = 0; i < BLOCK_SIZE; i++) {
    ret.bit[i] = (this->bit[i] - b.bit[i] + (1 << BIT_SIZE)) % (1 << BIT_SIZE);
  }
  return ret;
}

Block Block::operator^(const Block& b) const {
  Block ret(BIT_SIZE);
  for(int i = 0; i < BLOCK_SIZE; i++) {
    ret.bit[i] = this->bit[i] ^ b.bit[i];
  }
  return ret;
}

Block Block::operator<<(int num) const {
  Block ret(BIT_SIZE);
  for(int i = 0; i < BLOCK_SIZE; i++) {
    ret.bit[i] = this->bit[(i + num) % BLOCK_SIZE];
  }
  return ret;
}

Block Block::operator>>(int num) const {
  Block ret(BIT_SIZE);
  for(int i = 0; i < BLOCK_SIZE; i++) {
    ret.bit[i] = this->bit[(i - num + BLOCK_SIZE) % BLOCK_SIZE];
  }
  return ret;
}

/* rotate the byte/hex matrix clockwise 90 degree */
Block Block::rotate() {
  Block ret(BIT_SIZE);
  for(int t = 0; t < BLOCK_SIZE; t++) {
    int i = t / SIDE_SIZE;
    int j = t % SIDE_SIZE;
    int newi = j;
    int newj = SIDE_SIZE - 1 - i;
    ret.bit[newi * SIDE_SIZE + newj] = this->bit[t];
  }
  return ret;
}

Block Block::transpose() {
  Block ret(BIT_SIZE);
  for(int t = 0; t < BLOCK_SIZE; t++) {
    int i = t / SIDE_SIZE;
    int j = t % SIDE_SIZE;
    ret.bit[i * SIDE_SIZE + j] = this->bit[t];
  }
  return ret;
}

/**
 * E function for ciphering byte (8 bit)
 * Used in CBC
 **/
Block Block::e_encrypt(Block key) {
  Block ret(BIT_SIZE);
  Keygen keygen;
  ret = (*this >> 6) ^ (key << 9);
  ret = ret.rotate();
  ret = ret + key;
  ret = ret.rotate().rotate().rotate();
  ret = Block(BIT_SIZE, keygen.nextKey(ret.bit, BIT_SIZE));
  ret = ret.transpose();
  ret = ret ^ key;
  ret = ret.rotate().rotate();
  return ret;
}

/**
 * E function for deciphering byte (8 bit)
 * Used in CBC
 **/
Block Block::e_decrypt(Block key) {
  Block ret(BIT_SIZE);
  ret = this->rotate().rotate();
  ret = ret ^ key;
  ret = ret.transpose();
  ret = Block(BIT_SIZE, keygen.prevKey(ret.bit, BIT_SIZE));
  ret = ret.rotate();
  ret = ret - key;
  ret = ret.rotate().rotate().rotate();
  
  return ret;
}

/**
 * F function for ciphering hex (4 bit)
 * Used in Feistel network
 * Basically the algo is the same with E function in CBC so just call the subprogram :)
 **/
Block Block::f_encrypt(Block key) {
  return e_encrypt(key);
}

/**
 * F function for deciphering hex (4 bit)
 * Used in Feistel network
 **/
Block Block::f_decyprt(Block key) {
  return e_decrypt(key);
}

#endif