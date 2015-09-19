#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  char color;
  struct node *left,*right,*p;
}node;
node *new_node(int key)
{
  node *n = (node*)malloc(sizeof(*n));
  n->key = key;
  n->left = n->right = n->p = NULL;
  n->color = 'R';
  return n;
}
node *nil()
{
  static node * n = NULL;
  if(n==NULL)
  {
    n = (node*)malloc(sizeof(struct node));
    n->color = 'B';
    n->left = n->right = n->p = NULL;
  }
  return n;
}
#define nil nil()
void left_rotate(node **root_ref,node *x)
{
  node *y = x->left;
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
  x->p = y;
  y->left = x;
}
void right_rotate(node **root_ref,node *x)
{
  node *y = x->left;
  x->left = y->right;
  if(y->right !=nil)
  {
    y->right->p = x;
  }
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
void insert_fixup(node **root_ref,node *z)
{
  while(z->p->color == 'R')
  {
    node *y;
    if(z->p == z->p->p->left)
    {
      y = z->p->p->right;
      if(y->color == 'R')
      {
        z->p->color = 'B';
        y->color = 'B';
        z->p->p->color ='R';
        z = z->p->p;
      }
      else
      {
        if(z == z->p->right)
        {
          z = z->p;
          left_rotate(root_ref,z);
        }
        z->p->color = 'B';
        z->p->p->color = 'R';
        right_rotate(root_ref,z->p->p);
      }
    }
    else
    {
      y = z->p->p->left;
      if(y->color == 'R')
      {
        z->p->color = 'B';
        y->color = 'B';
        z->p->p->color = 'R';
        z = z->p->p;
      }
    }
  }
}
void insert(node **root_ref,int key)
{
  node *y = nil;
  node *x = *root_ref;
  node *z = new_node(key);
  while(x!=nil)
  {
    y = x;
    if(z->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  z->p = y;
  if(y==nil)
  {
    *root_ref = z;
  }
  else if(z->key < y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
  z->left = nil;
  z->right = nil;
  z->color = 'R';
  insert_fixup(root_ref,z);
}
void inorder(node *root)
{
  if(root!=nil)
  {
    inorder(root->left);
    printf(" %d ",root->key);
    inorder(root->right);
  }
}
void print_path(node *n)
{
}
/* Drier program to test above function*/
int main()
{
    struct node *root = nil;
    insert(&root,5);
    insert(&root,3);
    insert(&root,7);
    insert(&root,2);
    insert(&root,4);
    insert(&root,6);
    insert(&root,8);
    insert(&root,11);
    printf("inorder Traversal Is : ");
    inorder(root);
    puts("");
    return 0;
}
