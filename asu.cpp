#include <bits/stdc++.h>

using namespace std;

#define byte unsigned char

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

int main(int argc, char** argv) {
  vector<byte> v = read_binary(argv[1]);
  return 0;
}