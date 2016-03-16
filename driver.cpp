#include <bits/stdc++.h>

#include "block.h"
#include "bonek_algorithm.h"
#include "cbc.h"
#include "feistel.h"
#include "keygen.h"

using namespace std;

byte* a;

void print(Block b) {
  for(int i = 0; i < BLOCK_SIZE; i++) {
    printf("%d ", b.bit[i]);
  }
  printf("\n");
}

void print(vector<Block> b) {
  for(auto it : b) print(it);
}

int main() {
  a = new byte[BLOCK_SIZE];
  for(int i = 0; i < BLOCK_SIZE; i++) {
    a[i] = i;
  }
  for(int i = 0; i < BLOCK_SIZE; i++) printf("%d ", a[i]); printf("\n");
  Keygen keygen;
  byte* b = keygen.nextByteKey(a);
  for(int i = 0; i < BLOCK_SIZE; i++) printf("%d ", b[i]); printf("\n");
  a = keygen.prevByteKey(b);
  for(int i = 0; i < BLOCK_SIZE; i++) printf("%d ", a[i]); printf("\n");
  
  printf("\n\n");
  
  Block bl(8);
  print(bl);
  bl = bl.e_encrypt(Block(8, b));
  print(bl);
  bl = bl.e_decrypt(Block(8, b));
  print(bl);
  
  printf("\n\n");
  
  vector<Block> v;
  for(int i = 0; i < 5; i++) v.push_back(Block(8));
  printf("Ori\n");
  print(v);
  Cbc cbc;
  v = cbc.encrypt(v, b);
  printf("\n");
  printf("Encrypted :\n");
  print(v);
  v = cbc.decrypt(v, b);
  printf("\n");
  printf("Decrypted :\n");
  print(v);
  
  printf("\n\n");
  
  v.clear();
  
  for(int i = 0; i < 5; i++) v.push_back(Block(8));
  printf("Ori\n");
  print(v);
  Bonek bonek;
  v = bonek.encrypt(v, b);
  printf("\n");
  printf("Encrypted :\n");
  print(v);
  v = bonek.decrypt(v, b);
  printf("\n");
  printf("Decrypted :\n");
  print(v);
  /*
  printf("\n\n");
  
  Block p(8), fi(8), se(8);
  print(p);
  tie(fi, se) = p.split();
  print(fi);
  print(se);
  p.combine(fi, se);
  print(p);
  
  printf("\n\n");
  
  Block cok;
  tie(cok, ignore) = Block(8, b).split();
  b = cok.bit;
  
  Block c(8);
  print(c);
  Feistel feistel;
  c = feistel.encrypt(c, b);
  print(c);
  c = feistel.decrypt(c, b);
  print(c);
  */
  return 0;
}