#include <stdio.h>
#include "list.h"
bool is_even(struct node *t)
{
  return t->data %2==0;
}
int main()
{
  int arr[]={1,3,2,4,5};
  struct node *head = initList(arr,sizeof(arr)/sizeof(arr[0]));
  printList(head);
  remove_if(&head,is_even);
  printList(head);
}
