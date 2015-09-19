#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1
typedef struct node
{
  int key;
  int color;
  struct node *left;
  struct node *right;
  struct node *p;
} node;
/* global variable */
node *new_node(int key)
{
  node* n = (node*)malloc(sizeof(*n));
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  n->p = NULL;
  n->color = RED;
}
node* Nil = new_node(1);
int main()
{
}
