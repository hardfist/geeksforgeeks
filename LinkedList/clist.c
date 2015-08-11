#include <stdio.h>
#include <stdlib.h>
#include "clist.h"
void printList(struct node *n)
{
  if(n==NULL) return;
  struct node *curr = n;
  do
  {
    printf(" %d ",curr->data);
    curr = curr->next;
  }while(curr!=n);
  puts("");
}
void push(struct node **head_ref,int data)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = data;
  new_node->next = *head_ref;
  struct node *curr = *head_ref;
  if(*head_ref != NULL)
  {
    while(curr->next!=*head_ref)
    {
      curr = curr->next;
    }
    curr->next = new_node;
  }
  else
  {
    new_node->next = new_node;
  }
  *head_ref = new_node;
}
void splitList(struct node *head,struct node **head1_ref,
               struct node **head2_ref)
{
  if(head == NULL)
  {
    *head1_ref = NULL;
    *head2_ref = NULL;
    return;
  }
  if(head->next == head)
  {
    *head2_ref = head;
    *head1_ref = NULL;
    return;
  }
  struct node *prev = head;
  while(prev->next!=head)
  {
    prev = prev->next;
  }
  prev->next = NULL;
  struct node *tail = prev;
  struct node *slow = head;
  struct node *fast = head;
  prev = NULL;
  while(fast && fast->next)
  {
    prev = slow;
    slow = slow->next;
    fast = fast->next->next;
  }
  prev->next=head;
  tail->next = slow;
  *head1_ref = head;
  *head2_ref = slow;
  return;
}
void sortedInsert(struct node** head_ref,int data)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = data;
  new_node->next = NULL;
  struct node* curr = *head_ref;
  if(curr == NULL)
  {
    new_node->next = new_node;
    *head_ref = new_node;
  }
  else if(curr->data >= new_node->data)
  {
    while(curr->next != *head_ref)
    {
      curr = curr->next;
    }
    curr->next = new_node;
    new_node->next = *head_ref;
    *head_ref = new_node;
  }
  else
  {
    while(curr->next!=*head_ref && curr->next->data < new_node->data)
    {
      curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
  }
}
