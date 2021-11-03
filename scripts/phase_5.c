#include <stdio.h>

int main(int argc, char** argv)
{
  int i = 0;

  while (argv[1][i] != 0)
  {
    argv[1][i] = argv[1][i] + 2;
    i++;
  }
  printf("%s ", argv[1]);
  return 0;
}