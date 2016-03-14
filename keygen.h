#ifndef __KEYGEN_H_
#define __KEYGEN_H_

/* using Singleton design pattern to avoid multiple creation of instance */

#include "block.h"
#include "global.h"

struct Keygen {
  Keygen();
  Block nextHexKey(Block);
  Block nextByteKey(Block);
  Block nextKey(Block, int);
  
  static Keygen* instance;
  Block byte_table;
  Block hex_table;
};

Keygen::Keygen() {
  
}

/* generate next hexa key */
Block Keygen::nextHexKey(Block key) {
  
}

/* generate next byte key */
Block Keygen::nextByteKey(Block key) {
  
}

/**
 * bit_size : 4 (hexa key)
 *            8 (byte key)
 */
Block nextKey(Block key, int bit_size) {
  
}

#endif