#include <bits/stdc++.h>
#include <errno.h>

#include "bonek_algorithm.h"
#include "global.h"

using namespace std;

int getFileSize(FILE* file) {
  int l = ftell(file);
  fseek(file, 0, 2);
  int r = ftell(file);
  fseek(file, l, 0);
  return r;
}

vector<byte> read_binary(char* name) {
  printf("init %s length %d\n", name, strlen(name));
  vector<byte> plain;
  printf("Reading binary file...\n");
  FILE* file = fopen(name, "r");
  printf("file %d\n", file);
  printf("Error %d\n", errno);
  int fileSize = getFileSize(file);
  byte* filebuf = new byte[fileSize];
  printf("get filesize done\n");
  fread(filebuf, fileSize, 1, file);
  fclose(file);
  printf("pindah ke filebuf done\n");
  for(int i = 0; i < fileSize; i++) {
    plain.push_back((byte) filebuf[i]);
  }
  return plain;
}

void flush_to_file(vector<byte> output, char* name) {
  FILE* file = fopen(name, "wb");
  char* buffer = new char[output.size()];
  for(int i = 0; i < output.size(); i++) buffer[i] = output[i];
  fwrite(buffer, sizeof(byte), output.size(), file);
}

/* validate key, return true if key is correct */
bool check_key(char* s, int n) {
  for(int i = 0; i < n; i++) {
    if('a' <= s[i] && s[i] <= 'f') continue;
    if('0' <= s[i] && s[i] <= '9') continue;
    return 0;
  }
  return 1;
}

byte* hexa_to_byte(char* s) {
  int n = strlen(s);
  byte* ret = new byte[n / 2];
  for(int i = 0; i < n; i += 2) {
    int a = ('0' <= s[i] && s[i] <= '9'? s[i] - '0' : s[i] - 'a' + 10);
    int b = ('0' <= s[i+1] && s[i+1] <= '9'? s[i+1] - '0' : s[i+1] - 'a' + 10);
    ret[i/2] = (b << 4) | a;
  }
  return ret;
}


vector<Block> byte_to_block(vector<byte> b) {
  assert(b.size() % BLOCK_SIZE == 0);
  vector<Block> ret;
  for(int i = 0; i * BLOCK_SIZE < b.size(); i++) {
    ret.push_back(Block(8, reinterpret_cast<byte*> (&b[i])));
  }
  return ret;
}

vector<byte> block_to_byte(vector<Block> b) {
  vector<byte> ret;
  for(int i = 0; i < b.size(); i++) {
    for(int j = 0; j < BLOCK_SIZE; j++) {
      ret.push_back(b[i].bit[j]);
    }
  }
  return ret;
}
/*
e enc C:\Users\Luqman%20A.%20Siswanto\Code\bonek-encryption-algorithm/in.pdf out.pdf 00000aaaaa00000aaaaa00000aaaaafc
*/
int main(int argc, char** argv)
{
  errno = 0;
  if(argc != 5) {
    puts("Usage : main [enc/dec][file_masuk][file_keluar][key]");
    exit(0);
  }
  if(!check_key(argv[4], strlen(argv[4]))) {
    puts("Key invalid. Use 32 hexa char from 0..9 to a..f");
    exit(1);
  }
  printf("%s %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
  char* type = argv[1];
  char* file_in = argv[2];
  char* file_out = argv[3];
  byte* key = hexa_to_byte(argv[4]);
  printf("hexa to binary key done\n");
  
  vector<byte> v = read_binary(file_in);
  puts("Reading binary done");
  if(v.size() % BLOCK_SIZE) {
    int add = BLOCK_SIZE - v.size() % 16;
    printf("Adding %d bytes\n", add);
    while(add--) v.push_back(0);
  }
  vector<Block> from = byte_to_block(v), to;
  
  Bonek bonek;
  if(string(argv[1]) == "enc") {
    to = bonek.encrypt(from, key);
  } else {
    to = bonek.decrypt(from, key);
  }
  vector<byte> output = block_to_byte(to);
  flush_to_file(output, file_out);
  return 0;
}