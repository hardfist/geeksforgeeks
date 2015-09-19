#ifndef _BINOMIALHEAP_H
#define _BINOMIALHEAP_H
struct node
{
  int data;
  int k;
  struct node *head;
  struct node *next;
};
struct node *create(int k);
#endif
