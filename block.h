#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <algorithm>
#include "global.h"

/* Block is 128-bit, all constant defined in global.h */
struct Block {
  Block() {
    container = new byte[BLOCK_SIZE];
    fill(container, container + BLOCK_SIZE, 0);
  }
  Block(byte* b) {
    container = new byte[BLOCK_SIZE];
    for(int i = 0; i < BLOCK_SIZE; i++) {
      container[i] = b[i];
    }
  }
  byte get(int i) {
    return container[i];
  }
  void set(int i, byte b) {
    container[i] = b;
  }
  
  Block e_encrypt(byte*);
  Block e_decrypt(byte*);
  Block f_encrypt(byte*);
  Block f_decyprt(byte*);
  
  byte* container = NULL;
};

/**
 * E function for ciphering byte
 * Used in CBC
 **/
Block Block::e_encrypt(byte* key) {
  
}

/**
 * E function for deciphering byte
 * Used in CBC
 **/
Block Block::e_decrypt(byte* key) {
  
}

/**
 * F function for ciphering byte
 * Used in Feistel network
 **/
Block Block::f_encrypt(byte* key) {
  
}

/**
 * F function for deciphering byte
 * Used in Feistel network
 **/
Block Block::f_decyprt(byte* key) {
  
}

#endif