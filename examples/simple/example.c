#include <stdio.h>
#include <stdlib.h>
#include "abn.h"

void print_abn(abn_t op, char* name)
{
	char* representation = abn_to_string(op);
	printf("%s = [ 0x%s ]\n", name, representation);
	fflush(stdout);
	free(representation);
}

int main()
{
  srand(0);
  abn_t* a = abn_create(4);
  abn_t* b = abn_create(4);
  for(int i=0; i<4; i++)
  {
    a->chain[i] = rand();
    b->chain[i] = rand();
  }

  printf("# Created variables:\n");
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf("# a = a + b\n");
  abn_add(*a, *a, *b);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf("# b = a + b\n");
  abn_add(*b, *a, *b);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf("# a = 0\n");
  abn_reset(*a);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf("# a = b\n");
  abn_copy(a, *b);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf(" # a = a << 8\n");
  abn_shift_left(*a, 8);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf(" # a = a >> 8\n");
  abn_shift_right(*a, 8);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf(" # a = a << 4\n");
  abn_shift_left(*a, 4);
  print_abn(*a, "a");
  print_abn(*b, "b");

  printf(" # a = a >> 4\n");
  abn_shift_right(*a, 4);
  print_abn(*a, "a");
  print_abn(*b, "b");

	abn_free(a);
	abn_free(b);
}
