#include <bits/stdc++.h>

using namespace std;

int a[256], b[16];

int main() {
  for(int i = 0; i < 256; i++) a[i] = i;
  for(int i = 0; i < 16; i++) b[i] = i;
  
  srand(time(NULL));
  for(int i = 0; i < 256; i++) {
    int j = i + (rand() % (256 - i));
    swap(a[i], a[j]);
  }
  for(int i = 0; i < 16; i++) {
    int j = i + (rand() % (16 - i));
    swap(b[i], b[j]);
  }
  for(int i = 0; i < 256; i++) {
    printf(",%d", a[i]);
  }
  printf("\n");
   for(int i = 0; i < 16; i++) {
    printf(",%d", b[i]);
  }
  printf("\n");
  return 0;
}