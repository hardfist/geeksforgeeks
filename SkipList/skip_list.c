#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  struct node *left,*right;
}node;
node *new_node(int key)
{
  node* n = (node*)malloc(sizeof(struct node));
  n->key = key;
  n->left = n->right = NULL;
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
  node *y = x->right;
  x->right = y->left;
  y->left = x;
  return x;
}
node *splay(node *root,int key)
{
  if(root == NULL || root->key == key)
  {
    return root;
  }
  if(key < root->key)
  {
    if(root->left == NULL) return root;
    // LL
    if(key < root->left->key)
    {
      root->left->left = splay(root->left->left,key);
      root = right_rotate(root);
    }
    else if( key > root->key)
    {
      root->left->right = splay(root->left->right,key);
      if(root->left->right!=NULL)
      {
        root->left = left_rotate(root->left);
      }
    }
    return (root->left == NULL) ? root : right_rotate(root);
    
  }
  else
  {
    if(root->right == NULL) return root;
    if(key >  root->right->key)
    {
      root->right->right = splay(root->right->right,key);
      root = left_rotate(root);
    }
    else if(key < root->right->key)
    {
      root->right->left = splay(root->right->left,key);
      if(root->right->left !=NULL)
      {
        root->right = right_rotate(root->right);
      }
    }
    return root->right == NULL ? root : left_rotate(root);
  }
}
node *insert(node *root,int k)
{
  if(root == NULL) return new_node(k);
  root = splay(root,k);
  if(root->key == k) return root;
  node *n = new_node(k);
  if(k < root->key)
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
node *delete(node *root,int key)
{
  if(root == NULL) return NULL;
  if( key < root->left)
  {
    root->left = delete(root->left);
    if(root->left)
    {
      return right_rotate(root);
    }
  }
  else if(key > root->key)
  {
    root->right = delete(root->right);
    if(root->right)
    {
      return left_rotate(root);
    }
  }
  else
  {
    
  }
}
node *search(node *root,int key)
{
  return splay(root,key);
}
typedef void (*fun)(node *n);
void print(node *n)
{
  printf(" %d ",n->key);
}
void visit(node *r,fun pre,fun in,fun post)
{
  if(r)
  {
    if(pre) pre(r);
    visit(r->left,pre,in,post);
    if(in) in(r);
    visit(r->right,pre,in,post);
    if(post) post(r);
  }
}
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
    visit(root,print,NULL,NULL);
    puts("");
    printf("Inorder traversal of the modified Splay tree is \n");
    visit(root,NULL,print,NULL);
    puts("");
    return 0;
}
