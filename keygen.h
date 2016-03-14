#ifndef __KEYGEN_H_
#define __KEYGEN_H_

/* using Singleton design pattern to avoid multiple creation of instance */

#include "global.h"

struct Keygen {
  Keygen();
  byte* nextKey(byte*);
  
  static Keygen* instance = NULL;
  byte* byte_table;
  byte* hex_table;
};

Keygen::Keygen() {
  
}

byte* Keygen::nextKey(byte* key) {
  
}

#endif