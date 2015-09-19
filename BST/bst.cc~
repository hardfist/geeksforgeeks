#include <stdio.h>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
  struct node *parent;
};
struct node* new_node(int key)
{
  node* n = (node*)malloc(sizeof(*n));
  n->key = key;
  return n;
}
struct node* search(node *r,int key)
{
  while(r!=NULL && r->key != key)
  {
    if(key < r->key)
    {
      r = r->left;
    }
    else
    {
      r = r->right;
    }
  }
  return r;
}
void inorder(node *r)
{
  int N = 1000;
  int stk[N];
  int i = 0;
}
