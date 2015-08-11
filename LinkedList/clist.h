#ifndef _CLIST_H
#define _CLIST_H
struct node
{
  int data;
  struct node *next;
};
void push(struct node **head_ref,int data);
void printList(struct node *n);
void splitList(struct node *head,struct node **head1_ref,
               struct node **head2_ref);
void sortedInsert(struct node **head_ref,int new_data);
#endif
