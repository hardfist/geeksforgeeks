#include <stdio.h>
typedef struct node
{
  int *keys;
  node **children;
  int t;
  int n;
  bool leaf;
}node;
node *new_node(int t,bool leaf)
{
  node *n = (node*)malloc(sizeof(*n));
  n->keys = (int*)malloc(sizeof(int)*(2*t-1));
  n->children = (node**)malloc(sizoef(node*)*(2*t));
  n->leaf = leaf;
  n->t = t;
  n->n = 0;
  return n;
}
void visit(node *r)
{
  int i=0;
  for(i=0;i<r->n;i++)
  {
    if(!leaf)
    {
      visit(r->children[i]);
    }
    printf("%d ",r->keys[i]);
  }
  if(!leaf)
  {
    visit(r->children[i]);
  }
}
node* search(node *r,int key)
{
  int i=0;
  while(i<n && key > keys[i])
    i++;
  if(i<n && keys[i] == key)
  {
    return r;
  }
  if(leaf == true)
  {
    return false;
  }
  return search(r->children[i],key);
}
struct btree
{
  node *root;
  int t;
};
btree* new_btree(node *root,int t)
{
  btree *bt = (btree*)malloc(sizeof(*bt));
  bt->root = root;
  bt->t = t;
  return bt;
}
void insert(node **root_ref,int k,int t)
{
  if(*root_ref == NULL)
  {
    *root_ref = new_node(t,true);
    (*root_ref)->kesy[0] = k;
    (*root_ref)->n = 1;
  }
  else
  {
    if((*root_ref)->n == 2*t-1)
    {
      node* s = new_node(t,false);
      s->children[0]=*root_ref;
      splitchild(s,0,*root_ref);
      // 
      int i=0;
      if(s->keys[0] < key)
      {
        i++;
      }
      insertNonFull(s->children[i],k);
      *root_ref = s;
    }
    else
    {
      insertNonFull(*root_ref,k);
    }
  }
}
void insertNonFull(node *r,int k)
{
  int i = r->n-1;
  if(r->leaf == true)
  {
    while(i>=0 && keys[i]>k)
    {
      keys[i+1] = keys[i];
      i--;
    }
    keys[i+1] = k;
    root->n++;
  }else
  {
    while(i>=0 && keys[i]>k)
    {
      i--;
    }
    if(r->children[i+1]->n == 2*t-1)
    {
      splitchild(r,i+1,r->children[i+1]);
      if(keys[i+1]<k)
      {
        i++;
      }
    }
    C[i+1]->insertNonFull(k);
  }
}
