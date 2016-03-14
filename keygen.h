#ifndef __KEYGEN_H_
#define __KEYGEN_H_

/* using Singleton design pattern to avoid multiple creation of instance */

#include "global.h"

struct Keygen {
  Keygen();
  byte* nextHexKey(byte*);
  byte* nextByteKey(byte*);
  byte* nextKey(byte*, int);
  
  static Keygen* instance;
  byte* byte_table;
  byte* hex_table;
};

Keygen::Keygen() {
  
}

/* generate next hexa key */
byte* Keygen::nextHexKey(byte* key) {
  
}

/* generate next byte key */
byte* Keygen::nextByteKey(byte* key) {
  
}

/**
 * bit_size : 4 (hexa key)
 *            8 (byte key)
 */
byte* Keygen::nextKey(byte* key, int bit_size) {
  
}

#endif