#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int data;
  char color;
  struct node *left;
  struct node *right;
  struct node *parent;
} node;
void left_rotate(node **root_ref,node *x)
{
  // y stored pointer of right of x
  node *y = x->right;
  // store y's left subtree's pointer as x's right child
  x->right = y->left;
  // update parent pointer of x's right
  if(x->right !=NULL)
  {
    x->right->parent = x;
  }
  //update y's parent pointer
  y->parent = x->parent;

  //if x's parent is null make y as root of tree
  if(x->parent == NULL)
  {
    (*root_ref) = y;
  }
  else if(x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}
// Right Rotation
// Right Rotation (Similar to LeftRotate)
void right_rotate(struct node **root,struct node *y)
{
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}
void insertFixUp(struct node **root_ref,struct node *z)
{
  // iterate until z is not the root and z's parent color is red
  while(z!=*root_ref && z->parent->color == 'R')
  {
    struct node *y;
    // Find uncle and store uncle in y
    if(z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right;
    }
    else
    {
      y = z->parent->parent->left;
    }
    //If uncle is RED, do following
    // (i) Change color of parent and uncle as BLACK
    // (ii) Change color of grandparent as RED
    // (iii) Move z to grandparent
    if(y->color == 'R')
    {
      y->color = 'B';
      z->parent->color = 'B';
      z->parent->parent->color = 'R';
      z = z->parent->parent;
    }
    // Uncle is Black,there are founc case
    else
    {
      // Left-Left (LL) case ,do following
      //(i) Swap color of parent and grand parent
      // (ii) Right Rotate Grandparent
      if(z == z->parent->right)
      {
        z = z->parent; // case 2
        left_rotate(root_ref,z); // case 2
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        right_rotate(root_ref,z->parent->parent);
      }
      else
      {
        z = z->parent;
        right_rotate(root_ref,z);
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        left_rotate(root_ref,z->parent->parent);
      }
    }
  }
}
void insert(struct node **root_ref,int data)
{
  struct node *z = (struct node *)malloc(sizeof(struct node));
  z->data = data;
  z->left = z->right = z->parent = NULL;
  if(*root_ref == NULL)
  {
    z->color = 'B';
    (*root_ref)=z;
  }
  else
  {
    struct node *y = NULL;
    struct node *x = (*root_ref);
    while(x!=NULL)
    {
      y = x;
      if(z->data < x->data)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }
    z->parent = y;
    if(z->data > y->data)
    {
      y->right = z;
    }
    else
    {
      y->left = z;
    }
    z->color = 'R';
    insertFixUp(root_ref,z);
  }
}
// A utility function to traverse Red-Black tree in inorder fashion
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
/* Drier program to test above function*/
int main()
{
    struct node *root = NULL;
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
 
    return 0;
}
