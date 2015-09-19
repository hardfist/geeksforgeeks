#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1
#define nil Nil()
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
  return n;
}
node *Nil()
{
  static node *n=NULL;
  if(n==NULL)
  {
    n = new_node(-1);
    n->color = BLACK;
  }
  return n;
}
static void left_rotate(node **root_ref,node *x)
{
  node *y = x->right;
  x->right = y->left;
  if(y->left!=nil)
  {
    y->left->p = x;
  }
  y->p = x->p;
  if(x->p == nil)
  {
    *root_ref = y;
  }
  else if(x == x->p->left)
  {
    x->p->left = y;
  }
  else
  {
    x->p->right = y;
  }
  y->left = x;
  x->p = y;
}
static void right_rotate(node **root_ref,node *x)
{
  node *y = x->left;
  x->left = y->right;
  if(y->right!=nil)
  {
    y->right->p = x;
  }
  y->p = x->p;
  if(x->p == nil)
  {
    *root_ref = y;
  }
  else if(x == x->p->left)
  {
    x->p->left = y;
  }
  else
  {
    x->p->right = y;
  }
  y->right = x;
  x->p = y;
}
void fixup(node **root_ref,node *z)
{
  while(z->p->color == RED)
  {
    if(z->p == z->p->p->left)
    {
      y = z->p->p->right;
      if(y->color == RED)
      {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      }
      else if(z==z->p->right)
      {
        z = z->p;
        left_rotate(root_ref,z);
        z->p->color = BLACK;
        z->p->p->color = RED;
        right_rotate(root_ref,z);
      }
      else
      {
        
      }
    }
  }
  (*root_ref)->color = BLACK;
}
void insert(node **root_ref,int key)
{
  node *x = *root_ref;
  node *y = nil;
  node *n = new_node(key);
  while(x!=nil)
  {
    y = x;
    if(key < x->key) x = x->left;
    else x = x->right;
  }
  n->p = y;
  if(y==nil)
  {
    *root_ref = n;
  }
  else if(key < y->key)
  {
    y->left = n;
  }
  else
  {
    y->right = n;
  }
  n->left = nil;
  n->right = nil;
  n->color = RED;
  fixup(root_ref,n);
}
int main()
{
}
