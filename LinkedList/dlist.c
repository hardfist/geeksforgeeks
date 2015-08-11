#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dlist.h"
void printList(struct node *head)
{
  for(struct node *curr=head;curr!=NULL;curr=curr->next)
  {
    printf(" %d ",curr->data);
  }
  puts("");
}
struct node* make_node(int data)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->data = data;
  return new_node;
}
void push(struct node **head_ref,int new_data)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = new_data;
  new_node->next = (*head_ref);
  new_node->prev = NULL;
  if(*head_ref != NULL)
  {
    (*head_ref)->prev = new_node;
  }
  (*head_ref) = new_node;
}
void insertAfter(struct node* prev_node,int new_data)
{
  assert(prev_node!=NULL);
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = new_data;
  new_node->next = prev_node->next;
  new_node->prev = prev_node;
  if(new_node->next!=NULL)
  {
    new_node->next->prev = new_node;
  }
  prev_node->next = new_node;
}
void append(struct node **head_ref,int new_data)
{
  struct node *new_node = make_node(new_data);
  if(*head_ref == NULL)
  {
    *head_ref = new_node;
    return;
  }
  else
  {
    struct node *curr = *head_ref;
    while(curr->next!=NULL)
    {
      curr = curr->next;
    }
    new_node->prev = curr;
    curr->next = new_node;
    return;
  }
}
void deleteNode(struct node **head_ref,struct node *del)
{
  if(*head_ref == NULL || del == NULL)
    return;
  if(del->prev)
  {
    del->prev->next = del->next;
  }
  if(del->next)
  {
    del->next->prev = del->prev;
  }
  if(*head_ref == del)
  {
    *head_ref = del->next;
  }
  free(del);
}
void reverse(struct node **head_ref)
{
  struct node *prev = NULL;
  struct node *next = NULL;
  struct node *curr = *head_ref;
  while(curr != NULL)
  {
    next = curr->next;
    curr->next = prev;
    if(prev)
    {
      prev->prev = curr;
    }
    prev = curr;
    curr = next;
  }
  *head_ref = prev;
  if(prev) prev->prev = NULL;
}
static void swap(int *a,int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
struct node *lastNode(struct node *root)
{
  while(root && root->next)
  {
    root = root->next;
  }
  return root;
}
struct node *partition(struct node *lo,struct node *hi)
{
  //  printf("%d %d\n",lo->data,hi->data);
  int pivot = hi->data;
  struct node *t = lo;
  for(struct node *curr=lo;curr!=hi;curr=curr->next)
  {
    if(curr->data <= pivot)
    {
      swap(&(t->data),&(curr->data));
      t=t->next;
    }
  }
  swap(&(t->data),&(hi->data));
  return t;
}
void quickSortRecur(struct node *lo,struct node *hi)
{
  if(lo == NULL || hi == NULL || lo == hi || hi->next == lo)
  {
    return;
  }
  struct node *p = partition(lo,hi);
  quickSortRecur(lo,p->prev);
  quickSortRecur(p->next,hi);
}
void quickSort(struct node *head)
{
  struct node *h = lastNode(head);
  quickSortRecur(head,h);
}
