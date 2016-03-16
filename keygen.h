#ifndef __KEYGEN_H_
#define __KEYGEN_H_

/* using Singleton design pattern to avoid multiple creation of instance */

#include <cassert>

#include "global.h"

struct Keygen {
  Keygen();
  void init();
  byte* nextHexKey(byte*);
  byte* nextByteKey(byte*);
  byte* nextKey(byte*, int);
  byte* prevHexKey(byte*);
  byte* prevByteKey(byte*);
  byte* prevKey(byte*, int);
  
  static bool created;
  static byte* rev_byte_table;
  static byte* rev_hex_table;
};

bool Keygen::created = false;
byte* Keygen::rev_byte_table = NULL;
byte* Keygen::rev_hex_table = NULL;

Keygen::Keygen() {
  if(!created) {
    init();
    created = true;
  }
}

void Keygen::init() {  
  rev_byte_table = new byte[256];
  rev_hex_table = new byte[16];
  for(int i = 0; i < 256; i++) rev_byte_table[byte_table[i]] = i;
  for(int i = 0; i < 16; i++) rev_hex_table[hex_table[i]] = i;
}

/* generate next hexa key */
byte* Keygen::nextHexKey(byte* key) {
  byte* p = new byte[BLOCK_SIZE];
  for(int i = 0; i < BLOCK_SIZE; i++) {
    p[i] = hex_table[key[i]];
  }
  return p;
}

/* generate next byte key */
byte* Keygen::nextByteKey(byte* key) {
  byte* p = new byte[BLOCK_SIZE];
  for(int i = 0; i < BLOCK_SIZE; i++) {
    p[i] = byte_table[key[i]];
  }
  return p;
}

/**
 * bit_size : 4 (hexa key)
 *            8 (byte key)
 */
byte* Keygen::nextKey(byte* key, int bit_size) {
  if(bit_size == 4) {
    return nextHexKey(key);
  }
  if(bit_size == 8) {
    return nextByteKey(key);
  }
  assert(false);
}

/* generate previous hexa key */
byte* Keygen::prevHexKey(byte* key) {
  byte* p = new byte[BLOCK_SIZE];
  for(int i = 0; i < BLOCK_SIZE; i++) {
    p[i] = rev_hex_table[key[i]];
  }
  return p;
}

/* generate previous byte key */
byte* Keygen::prevByteKey(byte* key) {
  byte* p = new byte[BLOCK_SIZE];
  for(int i = 0; i < BLOCK_SIZE; i++) {
    p[i] = rev_byte_table[key[i]];
  }
  return p;
}

/**
 * bit_size : 4 (hexa key)
 *            8 (byte key)
 */
byte* Keygen::prevKey(byte* key, int bit_size) {
  if(bit_size == 4) {
    return prevHexKey(key);
  }
  if(bit_size == 8) {
    return prevByteKey(key);
  }
  assert(false);
}

#endif