#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
  int height;
}node;
node* new_node(int key)
{
  node* n = malloc(sizeof(struct node));
  if(n == NULL) return NULL;
  n->key = key;
  n->left = n->right = NULL;
  n->height = 1;
  return n;
}
int max(int a,int b)
{
  return a > b ? a : b;
}
int height(node *n)
{
  return n == NULL ? 0 : n->height;
}
int get_balance(node *n)
{
  if(n == NULL) return 0;
  else
  {
    return height(n->left) - height(n->right);
  }
}
void print(node *n)
{
  printf(" %d ",n->key);
}
void inorder(node *n,void (*fun)(node *n))
{
  if(n)
  {
    inorder(n->left,fun);
    fun(n);
    inorder(n->right,fun);
  }
}
node *left_rotate(node *r)
{
  node *y = r->right;
  r->right = y->left;
  y->left = r;
  r->height = max(height(r->left),height(r->right))+1;
  y->height = max(height(r->right),height(r->left))+1;
  return y;
}
node *right_rotate(node *r)
{
  node *y = r->left;
  r->left = y->right;
  y->right = r;
  r->height = max(height(r->left),height(r->right))+1;
  y->height = max(height(r->left),height(r->right))+1;
  return y;
}
node *fixup(node *root)
{
  int balance = get_balance(root);
  if(balance >1 && get_balance(root->left)>=0)
  {
    return right_rotate(root);
  }
  if(balance >1 && get_balance(root->left)<0)
  {
    root->left = left_rotate(root->left);
    return right_rotate(root);
  }
  if(balance < -1 && get_balance(root->right)<=0)
  {
    return left_rotate(root);
  }
  if(balance < -1 && get_balance(root->right)>0)
  {
    root->right = right_rotate(root->right);
    return left_rotate(root);
  }
  return root;
}
node *insert(node *root,int key)
{
  if(root==NULL)
  {
    return new_node(key);
  }
  if(key < root->key)
  {
    root->left = insert(root->left,key);
  }else
  {
    root->right = insert(root->right,key);
  }
  root->height = max(height(root->left),height(root->right))+1;
  root = fixup(root);
  return root;
}
node *delete(node *root,int key)
{
  if(root==NULL) return NULL;
  if(key < root->key)
  {
    root->left = delete(root->left,key);
  }
  else if(key > root->key)
  {
    root->right = delete(root->right,key);
  }
  else
  {
    node *tmp =root;
    if(root->right == NULL)
    {
      root = root->left;
      free(tmp);
    }
    else if(root->right->left == NULL)
    {
      root->right->left = root->left;
      root = root->right;
      free(tmp);
    }
    else
    {
      node *y = root->right;
      while(y->left!=NULL)
      {
        y = y->left;
      }
      root->key = y->key;
      root->right = delete(root->right,y->key);
    }
    if(root == NULL) return NULL;
    root->height = max(height(root->left),height(root->right))+1;
    root = fixup(root);
  }
  return root;
}
int main()
{
  const int n = 100;
  node *root = NULL;
  for(int i=0;i<n;i++)
  {
    root = insert(root,i);
  }
  //  inorder(root,print);
  puts("");
  printf(" %d ",height(root));
  puts("");
  for(int i=0;i<n/2;i++)
  {
    root = delete(root,i);
    puts("");
  }
  inorder(root,print);
  puts("");
  printf(" %d ",height(root));
}
