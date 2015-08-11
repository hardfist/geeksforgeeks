#ifndef _DLIST_H
#define _DLIST_H
struct node
{
  int data;
  struct node *next;
  struct node *prev;
};
struct node* make_node(int data);
void printList(struct node *head);
void push(struct node **head_ref,int new_data);
void append(struct node **head_ref,int new_data);
void insertAfter(struct node *prev,int new_data);
void deleteNode(struct node **head_ref,struct node *del);
void reverse(struct node **head_ref);
void quickSort(struct node *head);
#endif
