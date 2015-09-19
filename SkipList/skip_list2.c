#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
}node;
node* new_node(int key)
{
  node *n = (node*)malloc(sizeof(struct node));
  n->left = n->right = NULL;
  n->key = key;
  return n;
}
node *right_rotate(node *x)
{
  node *y = x->left;
  x->left = y->right;
  y->right = x;
  return y;
}
node *left_rotate(node *x)
{
  node *y=x->right;
  x->right =y->left;
  y->left = x;
  return y;
}
node *splay(node *root,int key)
{
  if(root == NULL || root->key == key) return root;
  if(key < root->key)
  {
    if(root->left == NULL) return root;
    if(key < root->left->key)
    {
      root->left->left = splay(root->left->left,key);
      root = right_rotate(root);
    }
    else if (key > root->left->key)
    {
      root->left->right =splay(root->left->right,key);
      if(root->left->right)
      {
        root->left = left_rotate(root->left);
      }
    }
    return root->left == NULL ? root : right_rotate(root);
  }
  else
  {
    if(root->right == NULL) return root;
    if(key > root->right->key)
    {
      root->right->right = splay(root->right->right,key);
      root = left_rotate(root);
    }
    else if(key < root->right->key)
    {
      root->right->left = splay(root->right->left,key);
      if(root->right->left)
      {
        root->right = right_rotate(root->right);
      }
    }
    return root->right == NULL ? root : left_rotate(root);
  }
  return root;
}
node *search(node *root,int key)
{
  return splay(root,key);
}
node *insert(node *root,int key)
{
  if(root == NULL) return new_node(key);
  if(root->key == key) return root;
  node *n = new_node(key);
  root = splay(root,key);
  if(n->key < root->key)
  {
    n->right = root;
    n->left = root->left;
    root->left = NULL;
  }
  else
  {
    n->left = root;
    n->right = root->right;
    root->right = NULL;
  }
  return n;
}
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
 
/* Drier program to test above function*/
int main()
{
    struct node *root = new_node(100);
    root->left = new_node(50);
    root->right = new_node(200);
    root->left->left = new_node(40);
    root->left->left->left = new_node(30);
    root->left->left->left->left = new_node(20);
    root = insert(root, 25);
    printf("Preorder traversal of the modified Splay tree is \n");
    preOrder(root);
    return 0;
}
