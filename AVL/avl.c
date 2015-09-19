#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
}node;
node* new_node(int key)
{
  node * n = (node*)malloc(sizeof(struct node));
  n->left = n->right = NULL;
  n->key = key;
  return n ;
}
void inorder(node *r,void (*fun)(node *))
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
  node *n = new_node(key);
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
  *ptr_ref = n;
}
node *min(node *r)
{
  assert(r);
  while(r->left)
  {
    r = r->left;
  }
  return r;
}

node* delete(node *r,int key)
{
  if(r==NULL) return NULL;
  if(key < r->key)
  {
    r->left = delete(r->left,key);
    return r;
  }
  else if(key > r->key)
  {
    r->right = delete(r->right,key);
    return r;
  }
  else
  {
    node *save = NULL;
    if(r->right== NULL)
    {
      save =r;
      r = r->left;
      free(save);
      return r;
    }
    else if(r->right->left == NULL)
    {
      save = r;
      r->right->left = r->left;
      r = r->right;
      free(save);
      return r;
    }
    else
    {
      node *p = r->right;
      node * y = p->left;
      while(y->left)
      {
        p = y;
        y = p->left;
      }
      p->left = y->right;
      y->right=r->right;
      save = r;
      y->left = r->left;
      r = y;
      free(save);
      return r;
    }
  }
}
void delete2(node **root_ref,int key)
{
  node **ptr_ref = root_ref;
  while(*ptr_ref && (*ptr_ref)->key != key)
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
  if(*ptr_ref == NULL) return;
  node *z = *ptr_ref;
  if(z->right == NULL)
  {
    *ptr_ref = z->left;
    free(z);
  }
  else if(z->right->left==NULL)
  {
    node *y = z->right;
    y->left = z->left;
    *ptr_ref = y;
    free(z);
  }
  else
  {
    node** y_ref =&(z->right);
    while((*y_ref)->left)
    {
      y_ref = &(*y_ref)->left;
    }
    node *y = *y_ref;
    *y_ref = y->right;
    y->left = z->left;
    y->right = z->right;
    *ptr_ref = y;
    free(z);
  }
}
void print(node *n)
{
  printf(" %d ",n->key);
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
  /* int a[] = {4,2,6,1,3,5,7}; */
  /* int b[] = {4,2,6,1,3,5,7}; */
  for(int i=0;i<n;i++)
  {
    a[i]=rand()%100;
    b[i] = a[i];
  }
  qsort(b,n,sizeof(b[0]),cmp);
  for(int i=0;i<n;i++)
  {
    printf(" %d ",b[i]);
  }
  puts("");
  node * root = NULL;
  for(int i=0;i<n;i++)
  {
    insert(&root,a[i]);
  }
  inorder(root,print);
  puts("");
  for(int i=0;i<n;i++)
  {
    delete2(&root,a[i]);
    inorder(root,print);
    puts("");
  }
}
