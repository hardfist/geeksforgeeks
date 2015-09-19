#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 256
struct SuffixTreeNode
{
  struct SuffixTreeNode *children[MAX_CHAR];
  struct SuffixTreeNode *suffixLink;
  int start;
  int *end;
}
