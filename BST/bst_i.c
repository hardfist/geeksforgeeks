#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
}node;
node *new_node(int key)
{
  node* n = (node*)malloc(sizeof(struct node));
  n->key = key;
  n->left = n->right = NULL;
  return n;
}
void print(node *n)
{
  assert(n);
  printf(" %d ",n->key);
}
void inorder(node *r,void (*fun)(node *n))
{
  if(r)
  {
    inorder(r->left,fun);
    fun(r);
    inorder(r->right,fun);
  }
}
void insert(node **root_ref,int key)
{
  node **ptr_ref = root_ref;
  while(*ptr_ref)
  {
    if(key < (*ptr_ref)->key)
    {
      ptr_ref = &(*ptr_ref)->left;
    }
    else
    {
      ptr_ref = &(*ptr_ref)->right;
    }
  }
  node *n = new_node(key);
  *ptr_ref = n;
}
void delete(node **root_ref,int key)
{
  node **ptr_ref = root_ref;
  while(*ptr_ref && (*ptr_ref)->key != key)
  {
    if( key < (*ptr_ref)->key)
    {
      ptr_ref = &(*ptr_ref)->left;
    }
    else
    {
      ptr_ref = &(*ptr_ref)->right;
    }
  }
  if(*ptr_ref == NULL) return;
  node *z = *ptr_ref;
  if(z->right == NULL)
  {
    *ptr_ref = z->left;
    free(z);
  }
  else if(z->right->left == NULL)
  {
    node *y = z->right;
    y->left = z->left;
    *ptr_ref = y;
    free(z);
  }else
  {
    node **y_ref = &(z->right);
    while((*y_ref)->left)
    {
      y_ref = &(*y_ref)->left;
    }
    node *y = *y_ref;
    *y_ref = y->right;
    y->right = z->right;
    y->left = z->left;
    *ptr_ref = y;
    free(z);
  }
}
int cmp(const void *a,const void *b)
{
  return *(int*)a - *(int*)b;
}
int main()
{
  const int n = 20;
  int a[n];
  int b[n];
  for(int i=0;i<n;i++)
  {
    a[i] = rand()%100;
    b[i] = a[i];
  }
  qsort(b,n,sizeof(b[0]),cmp);
  for(int i=0;i<n;i++)
  {
    printf(" %d ",b[i]);
  }
  puts("");
  node* root = NULL;
  for(int i=0;i<n;i++)
  {
    insert(&root,a[i]);
  }
  for(int i=0;i<n;i++)
  {
    inorder(root,print);
    puts("");
    delete(&root,a[i]);
  }
}
