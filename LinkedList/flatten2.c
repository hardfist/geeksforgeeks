#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define SIZE(a) (sizeof(a)/sizeof(a[0]))
struct node;
struct queue_node
{
  struct node *data;
  struct queue_node * next;
};
struct queue_node *head;
struct queue_node *tail;
struct queue_node *new_queue_node(struct node *data)
{
  struct queue_node* node = (struct queue_node*)malloc(sizeof(struct queue_node));
  node->next = NULL;
  node->data = data;
  return node;
}
void init()
{
  head = tail = NULL;
}
void enqueue(struct node* data)
{
  if(head == NULL)
  {
    head = tail = new_queue_node(data);
  }
  else
  {
    tail->next = new_queue_node(data);
    tail = tail->next;
  }
}
bool empty()
{
  return head == NULL;
}
struct node* deque()
{
  struct node *res = head->data;
  head = head->next;
  if(head == NULL)
  {
    tail = NULL;
  }
  return res;
}
struct node
{
  int data;
  struct node *next;
  struct node *child;
};
void flatten(struct node *n)
{
  if(n == NULL) return;
  struct node *curr = n;
  struct node *prev = NULL;
  init();
  enqueue(curr);
  while(!empty())
  {
    struct node *t = deque();
    if(prev!=NULL)
    {
      prev->next = t;
    }
    while(t!=NULL)
    {
      //      printf(" %d ",t->data);
      if(t->child!=NULL)
      {
        enqueue(t->child);
      }
      prev = t;
      t = t->next;
    }
  }
}
struct node *createList(int *arr,int n)
{
  struct node *head = NULL;
  struct node *p;
  for(int i=0;i<n;i++)
  {
    if(head == NULL)
    {
      head = p = (struct node*)malloc(sizeof(*p));
    }
    else
    {
      p->next = (struct node*)malloc(sizeof(*p));
      p = p->next;
    }
    p->data = arr[i];
    p->next = p->child = NULL;
  }
  return head;
}
void printList(struct node *head)
{
  while(head!=NULL)
  {
    printf(" %d ",head->data);
    head = head->next;
  }
  puts("");
}
struct node *createLists(void)
{
    int arr1[] = {10, 5, 12, 7, 11};
    int arr2[] = {4, 20, 13};
    int arr3[] = {17, 6};
    int arr4[] = {9, 8};
    int arr5[] = {19, 15};
    int arr6[] = {2};
    int arr7[] = {16};
    int arr8[] = {3};
 
    /* create 8 linked lists */
    struct node *head1 = createList(arr1, SIZE(arr1));
    struct node *head2 = createList(arr2, SIZE(arr2));
    struct node *head3 = createList(arr3, SIZE(arr3));
    struct node *head4 = createList(arr4, SIZE(arr4));
    struct node *head5 = createList(arr5, SIZE(arr5));
    struct node *head6 = createList(arr6, SIZE(arr6));
    struct node *head7 = createList(arr7, SIZE(arr7));
    struct node *head8 = createList(arr8, SIZE(arr8));
 
 
    /* modify child pointers to create the list shown above */
    head1->child = head2;
    head1->next->next->next->child = head3;
    head3->child = head4;
    head4->child = head5;
    head2->next->child = head6;
    head2->next->next->child = head7;
    head7->child = head8;
 
 
    /* Return head pointer of first linked list.  Note that all nodes are
       reachable from head1 */
    return head1;
}
int main()
{
  // test queue
  struct node *head = NULL;
  head = createLists();
  flatten(head);
  printList(head);
  return 0;
}
