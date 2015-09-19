#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
  int height;
}node;
int max(int a,int b) { return a > b ? a : b;}
int height(node *n)
{
  return n == NULL ? 0 : n->height;
}
node *new_node(int key)
{
  node* n =(node*)malloc(sizeof(struct node));
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;
  return n;
}
node *left_rotate(node *z)
{
  node *y = z->right;
  z->right = y->left;
  y->left = z;
  z->height = max(height(z->left),height(z->right))+1;
  y->height = max(height(y->left),height(y->right))+1;
  return y;
}
node* right_rotate(node *z)
{
  node *y = z->left;
  z->left = y->right;
  y->right = z;
  z->height = max(height(z->left),height(z->right))+1;
  y->height = max(height(y->left),height(y->right))+1;
  return y;
}
int get_blance(node *n)
{
  if(n==NULL) return 0;
  else
  {
    return height(n->left) - height(n->right);
  }
}
node *fixup(node *root)
{
   int balance = get_blance(root);
  if(balance > 1 && get_blance(root->left)>=0)
  {
    return right_rotate(root);
  }
  if(balance <-1 && get_blance(root->right)<=0)
  {
    return left_rotate(root);
  }
  if(balance >1 && get_blance(root->left) < 0)
  {
    root->left = left_rotate(root->left);
    return right_rotate(root);
  }
  if(balance <-1 && get_blance(root->right) >0)
  {
    root->right = right_rotate(root->right);
    return left_rotate(root);
  }
  return root;
}
node *insert(node *n,int key)
{
  if(n == NULL)
  {
    return new_node(key);
  }
  if(key < n->key)
  {
    n->left = insert(n->left,key);
  }
  else
  {
    n->right = insert(n->right,key);
  }
  n->height = max(height(n->left),height(n->right))+1;
  /* int balance = get_blance(n); */
  /* if(balance > 1 && key > n->left->key) */
  /* { */
  /*   n->left = left_rotate(n->left); */
  /*   return right_rotate(n); */
  /* } */
  /* if(balance < -1 && key < n->right->key) */
  /* { */
  /*   n->right = right_rotate(n->right); */
  /*   return left_rotate(n); */
  /* } */
  /* if(balance >1 && key < n->left->key) */
  /* { */
  /*   return right_rotate(n); */
  /* } */
  /* if(balance < -1 && key > n->right->key) */
  /* { */
  /*   return left_rotate(n); */
  /* } */
  n = fixup(n);
  return n;
}
node *delete_node(node *root,int key)
{
  if(root == NULL) return NULL;
  if( key < root->key)
  {
    root->left = delete_node(root->left,key);
  }
  else if(key > root->key)
  {
    root->right = delete_node(root->right,key);
  }
  else
  {
    node *tmp = root;
    if(root->right == NULL)
    {
      root = root->left;
      free(tmp);
    }
    else if(root->right->left  == NULL)
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
      root->right = delete_node(root->right,y->key);
    }
  }
  if(root == NULL) return NULL;
  root->height = max(height(root->left),height(root->right));
  root = fixup(root);
  return root;
}
void in_order(node *r)
{
  if(r)
  {
    in_order(r->left);
    printf(" %d ",r->key);
    in_order(r->right);
  }
}
/* Drier program to test above function*/
int main()
{
  struct node *root = NULL;
 
  /* Constructing tree given in the above figure */
  const int n = 1024;
  for(int i=0;i<n;i++)
  {
    root=insert(root,i);
  }
  /* printf("inorder traversal of the constructed AVL tree is \n"); */
  //  in_order(root);
  puts("");
  printf(" %d ",height(root));
  puts("");
  for(int i=0;i<n/2;i++)
  {
    root = delete_node(root,i);
    /* in_order(root); */
    /* puts(""); */
  }
  printf("after delete");
  //  in_order(root);
  puts("");
  printf(" %d ",height(root));
  puts("");
  return 0;
}
