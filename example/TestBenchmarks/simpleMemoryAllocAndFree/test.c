#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  size_t size = 1000000000;
  void *mem = malloc(size);
  printf("Successfully malloc'd %zu bytes at addr %p\n", size, mem);
  assert(mem != NULL);
  free(mem);
  printf("Successfully free'd %zu bytes from addr %p\n", size, mem);
  return 0;
}
