#ifndef __GLOBAL_H
#define __GLOBAL_H

/**
 * All global-defined constant defined here
 *
 */

#ifndef __BYTE_
#define __BYTE_
#define byte unsigned char
#endif

const int BLOCK_SIZE = 16;  // how many byte/hex per block
const int SIDE_SIZE = 4;    // SIDE_SIZE is always sqrt(BLOCK_SIZE)

#endif