#include <stdio.h>
struct node;
typedef struct entry
{
  int key;
  char *value;
  node *next;
}entry;
entry* new_entry(int key,char *value,node *next)
{
  entry *e = (entry*)malloc(sizeof(*e));
  e->key = key;
  e->value = value;
  e->next = next;
  return e;
}
typedef struct node;
{
  int m;
  entry **children;
}node;
node* new_node(int k)
{
  static int M = 4;
  node *n = (node*)malloc(sizeof(*n));
  n->m = k;
  n->children = (node**)malloc(sizeof(node*)*M);
  for(int i=0;i<M;i++)
  {
    children[i] = NULL;
  }
}
typedef struct btree
{
  node* root;
  int HT;
  int N;
}btree;
btree* new_btree()
{
  btree *bt= (btree*)malloc(sizeof(*bt));
  bt->root = new_node(0);
}
char* get(btree *bt,int key)
{
  return search(bt->root,key,bt->HT);
}
char *search(node *x,int key,int ht)
{
  node** children = x->children;
  if(ht == 0)
  {
    for(int i=0;i<x->m;i++)
    {
      if(children[i]->key == key) return children[i]->value;
    }
  }
  else
  {
    int i=0;
    while(i<x->m && key < children[i]->key)
    {
      i++;
    }
    return search(children[j]->next,key,ht-1);
  }
  return NULL;
}
