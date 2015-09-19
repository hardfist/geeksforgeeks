// C program for Red-Black Tree insertion
#include<stdio.h>
#include<stdlib.h>
 
//A Red-Black tree node structure
struct node
{
    int data;     // for data part
    char color;  // for color property
 
    //links for left, right children and parent
    struct node *left, *right, *parent;
};
// redefine NULL as nul
struct node *nul;
struct node *nil()
{
  if(nul==NULL)
  {
    nul = (struct node*)malloc(sizeof(struct node));
    nul->left = nul->right = nul->parent = NULL;
    nul->color = 'B';
  }
  return nul;
}
#undef NULL
#define NULL nil()
// Left Rotation
void LeftRotate(struct node **root,struct node *x)
{
    //y stored pointer of right child of x
    struct node *y = x->right;
 
    //store y's left subtree's pointer as x's right child
    x->right = y->left;
 
    //update parent pointer of x's right
    if (y->left != NULL)
        y->left->parent = x;
 
    //update y's parent pointer
    y->parent = x->parent;
 
    // if x's parent is null make y as root of tree
    if (x->parent == NULL)
        (*root) = y;
 
    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;
 
    // make x as left child of y
    y->left = x;
 
    //update parent pointer of x
    x->parent = y;
}
 
 
// Right Rotation (Similar to LeftRotate)
void rightRotate(struct node **root,struct node *y)
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
 
// Utility function to fixup the Red-Black tree after standard BST insertion
void insertFixUp(struct node **root,struct node *z)
{
    // iterate until z is not the root and z's parent color is red
    while (z->parent->color == 'R')
    {
      struct node *y;
      if(z->parent == z->parent->parent->left)
      {
        y = z->parent->parent->right;
        if(y->color == 'R')
        {
          z->parent->color = 'B';
          y->color='B';
          z->parent->parent->color = 'R';
          z = z->parent->parent;
        }
        else
        {
          if(z==z->parent->right)
          {
            z = z->parent;
            LeftRotate(root,z);
          }
          {
            z->parent->color ='B';
            z->parent->parent->color = 'R';
            rightRotate(root,z->parent->parent);
          }
        }
      }
      else
      {
        y = z->parent->parent->left;
        if(y->color == 'R')
        {
          z->parent->color = 'B';
          y->color='B';
          z->parent->parent->color = 'R';
          z = z->parent->parent;
        }else
        {
          if(z==z->parent->left)
          {
            z = z->parent;
            rightRotate(root,z);
            
          }
          {
            z->parent->color ='B';
            z->parent->parent->color = 'R';
            LeftRotate(root,z->parent->parent);
          }
        }
      }
    }
    (*root)->color = 'B'; //keep root always black
}
 
// Utility function to insert newly node in RedBlack tree
void insert(struct node **root, int data)
{
    // Allocate memory for new node
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = NULL;
 
     //if root is null make z as root
    if (*root == NULL)
    {
        z->color = 'B';
        (*root) = z;
    }
    else
    {
        struct node *y = NULL;
        struct node *x = (*root);
 
        // Follow standard BST insert steps to first insert the node
        while (x != NULL)
        {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (z->data > y->data)
            y->right = z;
        else
            y->left = z;
        z->color = 'R';
 
        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(root,z);
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
    puts("");
    return 0;
}
