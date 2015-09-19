#include "BinomialHeap.h"
#include <assert.h>
#include <stdlib.h>
#define swap(p,q,type) {type t = p;p=q;q=t;}
#define ROOT  -1

void level(struct node *root)
{
  
}
void push(struct node **head_ref,struct node *n)
{
  if(*head_ref == NULL)
  {
    *head_ref = n;
  }
  else
  {
    n->next = *head_ref;
    *head_ref = n;
  }
}
struct node *create(int data)
{
  struct node* new_node = (struct node*)malloc(sizeof(*new_node));
  new_node->k = 0;
  new_node->head = NULL;
  new_node->next = NULL;
  new_node->data = data;
  return new_node;
}
struct node *merge(struct node *p,struct node *q)
{
  assert(p->k == q->k);
  if(p->data > q->data)
  {
    swap(p,q,struct node *);
  }
  push(&(p->head),q);
  p->k++;
  return p;
}
int main()
{
  
}
