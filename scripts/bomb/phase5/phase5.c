#include <stdio.h>

int main(int argi, char **argv) {
   int index = 0;
   int tmp;
   char *arg = argv[1];
   char ret[100];
   char dict[] = "isrveawhobpnutfg"; // 15

  while (arg[index] != 0) {
    tmp = *(arg + index);
    tmp = tmp & 0xf; // 15
    tmp = *(tmp + dict);
    ret[index] = tmp;
    index = index + 1;
  }

  ret[index] = 0;
  return 0;
}