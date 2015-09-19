#include <stdio.h>
struct node
{
  int key;
  struct node *left;
  struct node *right;
};
struct node *new_node(int key)
{
  struct node *node = (struct node*)malloc(sizeof(struct node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  return node;
}
struct node *left_rotate(struct node *r)
{
  struct node *left = r->left;
  r->left = left->right;
  left->right = r;
  return left;
}
struct node *right_rotate(struct node *r)
{
  struct node *right = r->right;
  r->right = right->left;
  right->left = r;
  return right;
}
struct node *splay(struct node *root,int key)
{
  // case 1 : root is null
  // case 2 : match
  if(root == NULL || root->key == key)
  {
    return root;
  }
  if(key < root->key)
  {
    // case 3 : mismatch return parent
    if(root->left == NULL) return root;
    if(key < root->left->key)
    {
      root->left->left = splay(root->left->left,key);
      root = rightRotate(root);
    }
    else if(root->left->key < key)
    {
      root->left->right = splay(root->left->right,key);
      
    }
  }
}

