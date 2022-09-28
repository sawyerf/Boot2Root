#include <stdio.h>

char convert(char c) {
    char dict[] = "isrveawhobpnutfg";
    return dict[c & 0xf];
}

int main() {
  char c = 'a';
  char ret;
  int i = 0;
  char winner[] = "giants";

  while (i <= 5) {
    ret = convert(c);
    if (ret == winner[i]) {
      printf("%c", c);
      c = 'a';
      i++;
    }
    c++;
  }
}