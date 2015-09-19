#include "BinomialHeap.h"
#include <assert.h>
#include <stdlib.h>
#include <queue>
#define swap(p,q,type) {type t = p;p=q;q=t;}
#define ROOT  -1

void level(struct node *root)
{
  if(root == NULL) return;
  std::queue<struct node*> que;
  que.push(root);
  while(!que.empty())
  {
    struct node *top = que.front();
    que.pop();
    printf(" %d ",top->data);
    for(struct node *itr = top->head;itr!=NULL;itr=itr->next)
    {
      que.push(itr);
    }
  }
  printf("\n");
}
void push(struct node **head_ref,struct node *n)
{
  if(*head_ref == NULL)
  {
    *head_ref = n;
  }
  else
  {
    struct node *prev = *head_ref;
    while(prev->next!=NULL)
    {
      prev = prev->next;
    }
    prev->next = n;
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
struct node *mergeHeap(struct node *a,struct node *b)
{
  struct node *ha = a;
  struct node *hb = b;
  struct node *head = NULL;
  struct node *next = NULL;
  struct node *carry = NULL;
  while(a!=NULL && b!=NULL)
  {
    if(a->k == b->k)
    {
      next = a->next;
      
    }
  }
}
int main()
{
  int a[]={45,55,30,32,23,24,8,32};
  struct node* trees[8];
  for(int i=0;i<8;i++)
  {
    trees[i] = create(a[i]);
  }
  int k=4;
  while(k!=0)
  {
    for(int i=0;i<k;i++)
    {
      trees[i] = merge(trees[2*i],trees[2*i+1]);
    }
    k/=2;
  }
  level(trees[0])
}
