#include <stdio.h>
typedef struct list
{
  struct list * next;
  int foo;
  int bar;
}list;
int main()
{
  list *list;
  printf("%lu\n",sizeof(list));
}
