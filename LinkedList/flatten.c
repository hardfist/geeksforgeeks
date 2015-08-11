#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int data;
  struct node *right;
  struct node *down;
}node;
void push(node** head_ref,int new_data)
{
  node* new_node = (node*)malloc(sizeof(node));
  new_node->right = NULL;
  new_node->data = new_data;
  new_node->down = (*head_ref);
  (*head_ref) = new_node;
}
void printList(node *node)
{
  while(node!=NULL)
  {
    printf("%d ",node->data);
    node = node->down;
  }
}
node *merge(node *a,node *b)
{
  if(a==NULL) return b;
  if(b==NULL) return a;
  node *result;
  if(a->data < b->data)
  {
    result = a;
    result->down = merge(a->down,b);
  }
  else
  {
    result = b;
    result->down = merge(a,b->down);
  }
  return result;
}
node *flatten(node *root)
{
  if(root == NULL || root->right == NULL)
  {
    return root;
  }
  return merge(root,flatten(root->right));
}
int main()
{
    node* root = NULL;
 
    /* Let us create the following linked list
       5 -> 10 -> 19 -> 28
       |    |     |     |
       V    V     V     V
       7    20    22    35
       |          |     |
       V          V     V
       8          50    40
       |                |
       V                V
       30               45
    */
    push( &root, 30 );
    push( &root, 8 );
    push( &root, 7 );
    push( &root, 5 );
 
    push( &( root->right ), 20 );
    push( &( root->right ), 10 );
 
    push( &( root->right->right ), 50 );
    push( &( root->right->right ), 22 );
    push( &( root->right->right ), 19 );
 
    push( &( root->right->right->right ), 45 );
    push( &( root->right->right->right ), 40 );
    push( &( root->right->right->right ), 35 );
    push( &( root->right->right->right ), 20 );
 
    // Let us flatten the list
    root = flatten(root);
 
    // Let us print the flatened linked list
    printList(root);
 
    return 0;
}
