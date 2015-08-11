#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#define swap(x,y,type) do{ type tmp = x;x=y;y=tmp;}while(0)
#define max(a,b) ( (a) < (b) ?  b : a)
struct node *new_node(int data)
{
  struct node *node = (struct node*)malloc(sizeof(struct node));
  node->next = NULL;
  node->data = data;
  return node;
}
struct node *copyList(struct node *n)
{
  struct node *head = NULL;
  struct node **tail_ref = &head;
  for(struct node *curr = n;curr!=NULL;curr = curr->next)
  {
    *tail_ref = new_node(curr->data);
    (*tail_ref)->next = curr->next;
    tail_ref = &(*tail_ref)->next;
  }
  *tail_ref = NULL;
  return head;
}
struct node *nodedup(struct node *n)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = n->data;
  new_node->next = n->next;
  return new_node;
}
struct node* randList(int n)
{
  struct node *head=NULL;
  for(int i=0;i<n;i++)
  {
    push(&head,rand()%20);
  }
  return head;
}
struct node* randSortedList(int n)
{
  struct node *head = NULL;
  for(int i=0;i<n;i++)
  {
    insert_in_sorted(&head,rand()%20);
  }
  return head;
}
struct node* initList(int a[],int n)
{
  struct node *head = NULL;
  for(int i=0;i<n;i++)
  {
    append(&head,a[i]);
  }
  return head;
}
void printList(struct node *n)
{
  while( n != NULL)
  {
    printf(" %d ",n->data);
    n = n->next;
  }
  puts("");
};
void removeNode(struct node* node_ptr)
{
  struct node *temp = node_ptr->next;
  node_ptr->data = temp->data;
  node_ptr->next = temp->next;
  free(temp);
}
void printMiddle(struct node *head)
{
  // slow = n/2
  if(head == NULL) return;
  struct node *slow = head;
  struct node *fast = head;
  while( fast != NULL && fast->next !=NULL)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  printf("The middle element is [%d]\n\n",slow->data);
}
void printNthFromLast(struct node* head,int n)
{
  struct node *slow = head;
  struct node *fast = head;
  while(n-- && fast!=NULL)
  {
    fast = fast->next;
  }
  if(n!=-1) return;
  while(fast!=NULL)
  {
    slow = slow->next;
    fast = fast->next;
  }
  printf(" %d ",slow->data);
}
void deleteList(struct node** head_ref)
{
  if(*head_ref == NULL) return;
  struct node *prev = *head_ref;
  while(prev->next!=NULL)
  {
    struct node *tmp =prev->next;
    prev->next = tmp->next;
    free(tmp);
  }
  free(prev);
  *head_ref = NULL;
}
void push(struct node** head_ref,int new_data)
{
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = new_data;
  new_node->next = (*head_ref);
  (*head_ref) = new_node;
}
void insertAfter(struct node* prev_node,int new_data)
{
  assert(prev_node!=NULL);
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = new_data;
  new_node->next = prev_node->next;
  prev_node->next = new_node;
}
void append(struct node **head_ref,int new_data)
{
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->data = new_data;
  new_node->next = NULL;
  struct node *last = *head_ref;
  if(*head_ref == NULL)
  {
    *head_ref = new_node;
    return;
  }
  while(last->next !=NULL)
  {
    last = last->next;
  }
  last->next = new_node;
  return;
}
void deleteNode(struct node **head_ref,int key)
{
  struct node* prev = NULL;
  struct node* cur = *head_ref;
  while(cur != NULL && cur->data != key)
  {
    prev = cur;
    cur = cur->next;
  }
  if(cur !=NULL)
  {
    if(prev !=NULL)
    {
      prev->next = cur->next;
    }
    else
    {
      *head_ref = NULL;
    }
    free(cur);
  }
  return;
}
int getCount(struct node* head)
{
  int cnt = 0;
  while(head != NULL)
  {
    cnt++;
    head = head->next;
  }
  return cnt;
}
int getCount_r(struct node* head)
{
  return head == NULL ? 0 : 1 + getCount_r(head->next);
}
bool search(struct node* n,int x)
{
  while( n!= NULL && n->data !=x)
  {
    n = n->next;
  }
  return n != NULL;
}
bool search_r(struct node* n,int x)
{
  return  n == NULL ? false : (n->data == x || search_r(n->next,x));
}
int getNth(struct node *head,int index)
{
  while(index --  && head!=NULL)
  {
    head = head->next;
  }
  assert(head);
  return head->data;
}
int count(struct node *head,int search_for)
{
  int count = 0;
  while(head != NULL)
  {
    if(head -> data == search_for) count++;
    head = head->next;
  }
  return count;
}
void reverse(struct node **head_ref)
{
  if(*head_ref == NULL) return;
  struct node *prev = NULL;
  struct node *curr = *head_ref;
  struct node *next = curr->next;
  while(curr != NULL)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  *head_ref = prev;
}
bool healoop(struct node *n)
{
  struct node *slow = n;
  struct node *fast = n;
  while(fast && fast->next)
  {
    slow=slow->next;
    fast = fast->next->next;
    if(slow == fast)
    {
      return true;
    }
  }
  return false;
}
int compareList(struct node *first,struct node *second)
{
  while(first && second)
  {
    if(first->data < second->data) return -1;
    else if(first->data > second->data) return 1;
    first = first->next;
    second = second->next;
  }
  if(first == NULL && second == NULL) return 0;
  else if(first == NULL && second != NULL) return -1;
  else return 1;
}
bool isEqualList(struct node *first,struct node *second)
{
  while(first && second)
  {
    if(first->data != second->data) return false;
    first = first->next;
    second = second->next;
  }
  return !first && !second;
}
bool isPalindrome(struct node *n)
{
  if(n==NULL) return true;
  struct node *slow = n,*prev_of_slow = NULL;
  struct node *fast = n;
  struct node *midnode = NULL;
  while(fast && fast->next)
  {
    prev_of_slow = slow;
    slow = slow->next;
    fast = fast->next->next;
  }
  if(fast != NULL)
  {
    midnode = slow;
    slow = slow->next;
  }
  // split list to half
  prev_of_slow->next = NULL; // first_half
  struct node *second_half = slow;
  reverse(&second_half); // reverse second half
  bool res = isEqualList(n,second_half);
  reverse(&second_half); // recover second half
  if(midnode !=NULL)
  {
    prev_of_slow->next = midnode;
    midnode->next = second_half;
  }
  else
  {
    prev_of_slow->next = second_half;
  }
  return res;
}
void insert_node_in_sorted(struct node **head_ref,struct node *new_node)
{
  new_node->next = NULL;
  int new_data = new_node->data;
  struct node *prev = NULL;
  struct node *cur = *head_ref;
  while(cur!=NULL && cur->data < new_data)
  {
    prev = cur;
    cur = cur->next;
  }
  new_node->next = cur;
  if(prev!=NULL)
  {
    prev->next = new_node;
  }
  else
  {
    *head_ref = new_node;
  }
  return;
}
void insert_in_sorted(struct node **head_ref,int new_data)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->next = NULL;
  insert_node_in_sorted(head_ref,new_node);
}
void appendList(struct node **head_ref,struct node *tail)
{
  if(*head_ref == NULL)
  {
    *head_ref = tail;
  }
  struct node *prev= *head_ref;
  while(prev->next!=NULL)
  {
    prev = prev->next;
  }
  prev->next = tail;
}
int getIntesectionNode(struct node* head1,struct node* head2)
{
  int len1=getCount(head1);
  int len2=getCount(head2);
  if(len1 > len2)
  {
    swap(head1,head2,struct node*);
    swap(len1,len2,int);
  }
  // len1 < len2
  for(int i=len1;i<len2;i++)
  {
    head1 = head1->next;
  }
  while(head1 && head2)
  {
    if(head1 == head2 )
      break;
    head1 = head1->next;
    head2 = head2->next;
  }
  assert(head1&&head2);
  return head1->data;
}
void recursive_reverse_print(struct node *n)
{
  if(n == NULL) return;
  recursive_reverse_print(n->next);
  printf(" %d ",n->data);
}
void remove_duplicate_from_unsorted(struct node* n)
{
  if(n == NULL || n->next == NULL) return;
  struct node *prev = n;
  struct node *curr = n->next;
  while(curr!=NULL)
  {
    struct node *itr = n;
    while( itr != curr)
    {
      if(itr->data == curr->data) break;
      itr = itr->next;
    }
    if(itr!= curr)
    {
      prev->next = curr->next;
      free(curr);
      curr = prev->next;
    }
    else
    {
      prev = curr;
      curr = curr->next;
    }
  }
}
void remove_duplicate_from_sorted(struct node *n)
{
  if( n == NULL || n->next == NULL) return;
  struct node *prev = n;
  struct node *curr = n->next;
  while(curr!=NULL)
  {
    if(curr->data == prev->data)
    {
      prev->next= curr->next;
      free(curr);
      curr = prev->next;
    }
    else
    {
      prev = curr;
      curr = curr->next;
    }
  }
}
void pairWiseSwap(struct node *head)
{
  if(head == NULL || head->next == NULL) return;
  struct node *curr = head;
  while(curr!=NULL && curr->next!=NULL)
  {
    swap(curr->data,curr->next->data,int);
    curr = curr->next->next;
  }
}
void moveToFront(struct node **head_ref)
{
  assert(head_ref);
  if(*head_ref == NULL || (*head_ref)->next == NULL) return;
  struct node *prev = *head_ref;
  while(prev->next->next!=NULL)
  {
    prev=prev->next;
  }
  struct node *new_head = prev->next;
  prev->next = NULL;
  new_head->next = *head_ref;
  *head_ref = new_head;
}
struct node* sortedMerge(struct node *a,struct node *b)
{
  struct node dummy={-1,NULL}; // careful set dummy.next=NULL
  struct node* prev = &dummy;
  while(a!=NULL || b!= NULL)
  {
    if(a==NULL)
    {
      prev->next = nodedup(b);
      b = b->next;
    }
    else if(b==NULL)
    {
      prev->next = nodedup(a);
      a=a->next;
    }
    else if(a->data < b->data)
    {
      prev->next = nodedup(a);
      a=a->next;
    }
    else
    {
      prev->next = nodedup(b);
      b=b->next;
    }
    prev = prev->next;
  }
  return dummy.next;
}
struct node* sortedIntersect(struct node *a,struct node *b)
{
  struct node *new_head =NULL;
  struct node **lastPtrRef = &new_head;
  while(a!=NULL && b!=NULL)
  {
    if(a->data == b->data)
    {
      push(lastPtrRef,a->data);
      a=a->next;
      b=b->next;
      lastPtrRef=&(*lastPtrRef)->next;
    }
    else if(a->data < b->data)
    {
      a=a->next;
    }
    else
    {
      b=b->next;
    }
  }
  return new_head;
}
void deleteAlt(struct node *head)
{
  if(head == NULL || head->next == NULL) return;
  struct node *prev = head;
  while(prev && prev->next!=NULL)
  {
    struct node *next = prev->next;
    prev->next = next->next;
    free(next);
    prev = prev->next;
  }
  return;
}
static void moveNode(struct node **destRef,struct node** sourceRef)
{
  assert(destRef && sourceRef);
  if(*sourceRef == NULL) return;
  struct node *head = *sourceRef;
  *sourceRef = head->next;
  head->next = *destRef;
  *destRef = head;
}
void alteratingSplit(struct node *source,struct node** aRef,struct node** bRef)
{
  int i=0;
  while(source!=NULL)
  {
    if(i%2==0)
    {
      moveNode(aRef,&source);
    }
    else
    {
      moveNode(bRef,&source);
    }
    i++;
  }
}
bool isIdentical(struct node *a,struct node *b)
{
  if(!a && !b) return true;
  while(a && b)
  {
    if(a->data != b->data)
    {
      return false;
    }
    a=a->next;
    b=b->next;
  }
  return !a && !b;
}
void frontBackSplit(struct node *head,struct node **a_ref,struct node **b_ref)
{
  if(head == NULL) return;
  struct node *slow = head;
  struct node *fast = head;
  struct node *slow_prev = NULL;
  while(fast!=NULL && fast->next!=NULL)
  {
    fast = fast->next->next;
    slow_prev = slow;
    slow=slow->next;
  }
  if(slow_prev !=NULL)
  {
    *b_ref = slow_prev->next;
    slow_prev->next = NULL;
    *a_ref = head;
  }
  else
  {
    *a_ref = NULL;
    *b_ref = head;
  }
}
void mergeSort(struct node **head_ref)
{
  struct node *head = *head_ref;
  if(head == NULL || head->next == NULL) return;
  struct node *a=NULL;
  struct node *b=NULL;
  frontBackSplit(head,&a,&b);
  mergeSort(&a);
  mergeSort(&b);
  *head_ref = sortedMerge(a,b);
}
bool isSorted(struct node *n)
{
  if(n == NULL || n->next == NULL) return true;
  struct node *prev = n;
  struct node *cur = n->next;
  while(cur!=NULL)
  {
    if(cur->data < prev->data)
    {
      return false;
    }
    prev = cur;
    cur = cur->next;
  }
  return true;
}
struct node *reverseInGroups(struct node *head,int k)
{
  if(head == NULL || head->next == NULL) return head;
  struct node *prev = NULL;
  struct node *curr = head;
  struct node *next = NULL;
  for(int i=0;i<k && curr!=NULL;i++)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  head->next =reverseInGroups(curr,k);
  return prev;
}
struct node *kAltReverseHelper(struct node *head,int k,bool reverse)
{
  if(head == NULL || head->next == NULL) return head;
  struct node *prev = NULL;
  struct node *curr = head;
  struct node *next = NULL;
  if(reverse)
  {
    for(int i=0;i<k && curr!=NULL;i++)
    {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    head->next = kAltReverseHelper(curr,k,!reverse);
    return prev;
  }
  else
  {
    for(int i=0;i<k && curr!=NULL;i++)
    {
      prev = curr;
      curr = curr->next;
    }
    prev->next = kAltReverseHelper(curr,k,!reverse);
    return head;
  }
}
struct node *kAltReverse(struct node *head,int k)
{
  return kAltReverseHelper(head,k,true);
}
struct node *kAltReverse_i(struct node *head,int k)
{
  if(head == NULL || head->next == NULL) return head;
  struct node *prev = NULL;
  struct node *curr = head;
  struct node *next = NULL;
  for(int i=0;i<k && curr!=NULL;i++)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  head->next = curr;
  for(int i=0;i<k-1 && curr!=NULL;i++)
  {
    curr = curr->next;
  }
  if(curr!=NULL)
  {
    curr->next = kAltReverse(curr->next,k);
  }
  return prev;
}
void removeNodeByPtr(struct node **head_ref,struct node *n)
{
  if(*head_ref == n)
  {
    *head_ref = (*head_ref)->next;
    free(n);
    return;
  }
  struct node *prev = *head_ref;
  while(prev!=NULL && prev->next != n)
  {
    prev = prev->next;
  }
  assert(prev!=NULL);
  prev->next = n->next;
  free(n);
  return;
}
void delLesserNodes(struct node **head_ref)
{
  struct node *curr = *head_ref;
  while(curr!=NULL)
  {
    for(struct node *itr=*head_ref;itr!=curr;itr=itr->next)
    {
      if(itr->data < curr->data)
      {
        removeNodeByPtr(head_ref,itr);
      }
    }
    curr = curr->next;
  }
}
void delLesserNodes2(struct node **head_ref)
{
  if(*head_ref == NULL || (*head_ref)->next == NULL) return;
  reverse(head_ref);
  struct node *tail = *head_ref;
  struct node *curr = tail->next;
  struct node *next = NULL;
  while(curr!=NULL)
  {
    if(curr->data > tail->data)
    {
      tail->next = curr;
      tail = tail->next;
      curr = curr->next;
    }
    else
    {
      next = curr->next;
      free(curr);
      curr = next;
    }
  }
  tail->next = NULL;
}
// 1 3 5 7 2 4 5 6 8  => 2 4 5 6 8 1 3 5 7
void segregateEvenOdd(struct node **head_ref)
{
  if(*head_ref == NULL && (*head_ref)->next == NULL) return;
  struct node *tail = *head_ref;
  while(tail->next!=NULL)
  {
    tail = tail->next;
  }
  struct node *end = tail;

  // move front odd node to end
  struct node *curr = *head_ref;
  while(curr->data %2 !=0 && curr!=end)
  {
    tail->next = curr;
    curr = curr->next;
    tail = tail->next;
  }
  tail->next = NULL;
  struct node *prev = NULL;
  if(curr->data%2==0)
  {
    *head_ref = curr;
    while(curr!=end)
    {
      if((curr->data)%2 == 0)
      {
        prev = curr;
        curr = curr->next;
      }
      else
      {
        prev->next = curr->next;
        curr->next = NULL;
        tail->next = curr;
        tail = tail->next;
        curr = prev->next;
      }
    }
  }
  else
  {
    prev = curr;
  }

  if(tail!= end && (end->data)%2!=0)
  {
    prev->next = end->next;
    end->next = NULL;
    tail->next = end;
  }
  return;
}
static void removeLoop(struct node *loop_node,struct node *head)
{
  struct node *n1;
  struct node *n2;
  n1 = head;
  while(true)
  {
    for(n2=loop_node;n2->next!=loop_node && n2->next!=n1;n2=n2->next)
    {
    }
    if(n2->next == n1)
    {
      break;
    }
    else
    {
      n1 = n1->next;
    }
  }
  n2->next = NULL;
}
bool detectAndRemoveLoop(struct node *n)
{
  struct node *slow = n;
  struct node *fast = n;
  while(fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast)
    {
      removeLoop(slow,n);
      return true;
    }
  }
  return false;
}
struct node* addTwoLists(struct node* first,struct node *second)
{
  struct node* res = NULL;
  int sum = 0;
  int carry = 0;
  struct node *tmp = NULL;
  struct node *prev = NULL;
  while(first != NULL || second != NULL)
  {
    sum = carry + (first ? first->data : 0) + (second ? second->data : 0);
    carry = sum/10;
    tmp = new_node(sum%10);
    if(res == NULL)
    {
      res =  tmp;
    }
    else
    {
      prev->next = tmp;
    }
    prev = tmp;
    if(first) first = first->next;
    if(second) second = second->next;
  }
  if(carry > 0)
  {
    tmp->next = new_node(carry);
  }
  return res;
}
bool contains(struct node* n,int data)
{
  while(n!=NULL)
  {
    if(n->data == data) return true;
    n = n->next;
  }
  return false;
}
struct node *getUnion(struct node *a,struct node *b)
{
  struct node *result = NULL;
  struct node *t1 = a;
  struct node *t2 = b;
  while(t1 != NULL)
  {
    push(&result,t1->data);
    t1 = t1->next;
  }
  while(t2 != NULL)
  {
    if(!contains(result,t2->data))
    {
      push(&result,t2->data);
    }
    t2 = t2->next;
  }
  return result;
}
struct node *getIntesection(struct node *a,struct node *b)
{
  struct node *t1 = a;
  struct node *result = NULL;
  while( t1 != NULL)
  {
    if(contains(b,t1->data))
      push(&result,t1->data);
    t1 =t1->next;
  }
  return result;
}
bool isSumSorted(struct node *headA,struct node *headB,struct node *headC,int givenSum)
{
  struct node *a = headA;
  struct node *b = headB;
  struct node *c = headC;
  while(a!=NULL)
  {
    while(b!=NULL && c!=NULL)
    {
      int sum = a->data + b->data +c->data;
      if(sum == givenSum)
      {
        return true;
      }
      else if(sum < givenSum)
      {
        b = b->next;
      }
      else
      {
        c = c->next;
      }
    }
  }
  return false;
}
void rotate(struct node **head_ref,int k)
{
  if(k == 0) return;
  struct node *current = *head_ref;
  for(int i=0;i<k-1 && current!=NULL;i++)
  {
    current = current->next;
  }

  if(current == NULL)
  {
    return ;
  }
  struct node *kthNode = current;
  while(current->next !=NULL)
  {
    current = current->next;
  }
  current->next = *head_ref;
  *head_ref =kthNode->next;
  kthNode->next = NULL;
}
struct node *deepCopy(struct node *n)
{
  struct node *new_head = NULL;
  struct node **tail_ref = &new_head;
  for(struct node *cur = n;cur!=NULL;cur=cur->next)
  {
    struct node* copy = new_node(cur->data);
    *tail_ref = copy;
    tail_ref = &((*tail_ref)->next);
  }
  *tail_ref = NULL;
  return new_head;
}
void addCarryToRemaing(struct node *head1,node *cur,int* carry,struct node **result)
{
  int sum;
  if(head1!=cur)
  {
    addCarryToRemaing(head1->next,cur,carry,result);
    sum = head1->data + *carry;
    *carry = sum/10;
    sum %= 10;
    push(result,sum);
  }
}
struct node* addSameSize(struct node *head1,struct node *head2,int *carry)
{
  if(head1 == NULL)
  {
    return NULL;
  }
  int sum;
  struct node *result = (struct node*)malloc(sizeof(struct node));
  result->next = addSameSize(head1->next,head2->next,carry);
  sum = head1->data + head2->data + *carry;
  *carry = sum/10;
  sum = sum%10;
  result->data = sum;
  return result;
}
void addList(struct node *head1,struct node *head2,struct node **result)
{
  struct node *curr;
  if(head1 == NULL)
  {
    *result = head2;
  }
  if(head2 == NULL)
  {
    *result = head1;
  }
  int size1 =getCount(head1);
  int size2 = getCount(head2);
  int carry = 0;
  if(size1 == size2)
  {
    *result = addSameSize(head1,head2,&carry);
  }
  else
  {
    int diff = abs(size1 - size2);
    if(size1 < size2)
    {
      swap(head1,head2,struct node*);
    }
    for(curr = head1;diff--;curr=curr->next);
    *result = addSameSize(curr,head2,&carry);
    addCarryToRemaing(head1,curr,&carry,result);
  }
  if(carry)
  {
    push(result,carry);
  }
}
void sortList(struct node *head)
{
  int count[3] = {0,0,0};
  struct node *curr = head;
  while(curr!=NULL)
  {
    count[curr->data]++;
    curr=curr->next;
  }
  curr = head;
  int i=0;
  while(curr!=NULL)
  {
    if(count[i]!=0)
    {
      curr->data=count[i]--;
    }
    else
    {
      i++;
    }
    curr = curr->next;
  }
}
void skipMdeleteN(struct node *head,int m,int n)
{
  struct node *curr = head;
  struct node *prev = NULL;
  while(curr!=NULL)
  {
    for(int i=0;i<m && curr!=NULL;i++)
    {
      prev = curr;
      curr = curr->next;
    }
    if(curr == NULL) break;
    for(int i=0;i<n&& curr!=NULL;i++)
    {
      prev->next = curr->next;
      free(curr);
      curr = prev->next;
    }
  }
}
struct node *lastNode(struct node *head)
{
  while(head!=NULL && head->next!=NULL)
  {
    head = head->next;
  }
  return head;
}
struct node *partition(struct node *lo,struct node *hi,struct node **prev_ref)
{
  assert(lo && hi);
  //  printf("%d %d",lo->data,hi->data);
  int pivot = hi->data;
  struct node *prev = NULL;
  struct node *t = lo;
  for(struct node *curr=lo;curr!=hi;curr=curr->next)
  {
    if(curr->data <= pivot)
    {
      swap((t->data),(curr->data),int);
      prev = t;
      t=t->next;
    }
  }
  *prev_ref = prev;
  swap((t->data),(hi->data),int);
  return t;
}
void quickSortRecur(struct node *lo,struct node *hi)
{
  if(lo == NULL || hi == NULL || lo == hi || hi->next == lo)
  {
    return;
  }
  struct node *prev = NULL;
  struct node *p = partition(lo,hi,&prev);
  quickSortRecur(lo,prev);
  quickSortRecur(p->next,hi);
}
void quickSort(struct node *head)
{
  if(head == NULL) return;
  struct node *last = lastNode(head);
  quickSortRecur(head,last);
}
void merge(struct node *p,struct node **q_ref)
{
  struct node *q = *q_ref;
  struct node *prev = p;
  struct node *pnext = NULL;
  struct node *qnext = NULL;
  while(q!=NULL && prev!=NULL)
  {
    pnext = prev->next;
    qnext = q->next;
    prev->next = q;
    q->next = pnext;
    q = qnext;
    prev = pnext;
  }
  *q_ref = q;
}
void pairWiseSwap2(struct node **head_ref)
{
  if(*head_ref == NULL || (*head_ref)->next == NULL) return;
  struct node* prev = NULL;
  struct node* next = NULL;
  struct node *curr =*head_ref;
  while(curr!=NULL && curr->next!=NULL)
  {
    if(prev == NULL)
    {
      next = curr->next;
      *head_ref = next;
      curr->next = next->next;
      next->next = curr;
    }
    else
    {
      next = curr->next;
      prev->next = next;
      curr->next = next->next;
      next->next = curr;
    }
    prev = curr;
    curr = curr->next;
  }
}
struct linenode
{
  int x,y;
  struct linenode *next;
};
static bool isHorizontal(struct linenode *a,struct linenode *b)
{
  return a->y == b->y;
}
static bool isVertical(struct linenode *a,struct linenode *b)
{
  return a->x == b->x;
}
void pushLine(struct linenode **head_ref,int x,int y)
{
  struct linenode *new_node = (struct linenode*)malloc(sizeof(struct linenode));
  new_node->x = x;
  new_node->y = y;
  new_node->next = (*head_ref);
  *head_ref = new_node;
}
void printLineList(struct linenode *head)
{
  while(head!=NULL)
  {
    printf(" (%d,%d) ",head->x,head->y);
    head = head->next;
  }
}
struct linenode *deleteMiddle(struct linenode *head)
{
  if(head == NULL || head->next == NULL || head->next->next==NULL) return head;
  struct linenode *first = head;
  struct linenode *last = head;
  struct linenode *next = NULL;
  while(first!=NULL)
  {
    last = first->next;
    if(last == NULL) break;
    if(isVertical(first,last))
    {
      while(last->next!=NULL && isVertical(first,last->next))
      {
        next = last->next;
        free(last);
        last = next;
      }
      first->next = last;
    }
    else if(isHorizontal(first,last))
    {
      while(last->next!=NULL && isHorizontal(first,last->next))
      {
        next = last->next;
        free(last);
        last = next;
      }
      first->next = last;
    }
    else
    {
      assert(0);
    }
    first = last;
  }
  return head;
}
struct node* findMaxSumList(struct node *a,struct node *b)
{
  struct node *head = NULL;
  struct node **head_ref = &head;
  struct node *heada = NULL;
  struct node **heada_ref = &heada;
  struct node *headb = NULL;
  struct node **headb_ref = &headb;
  int suma = 0;
  int sumb = 0;
  while( a && b)
  {
    if(a->data < b->data)
    {
      suma +=a->data;
      *heada_ref = new_node(a->data);
      heada_ref = &(*heada_ref)->next;
      a=a->next;
    }
    else if(b->data < a->data)
    {
      sumb +=b->data;
      *headb_ref = new_node(b->data);
      headb_ref = &(*headb_ref)->next;
      b=b->next;
    }
    else
    {
      if(suma > sumb)
      {
        *head_ref = heada;
        head_ref = heada_ref;
      }
      else
      {
        *head_ref = headb;
        head_ref = headb_ref;
      }
      *head_ref = new_node(a->data);
      head_ref = &(*head_ref)->next;
      // init
      heada = NULL;
      headb = NULL;
      heada_ref = &heada;
      headb_ref = &headb;
      suma = sumb = max(suma,sumb);
      suma+=a->data;
      sumb+=b->data;
      a=a->next;
      b=b->next;
    }
  }
  while(a!=NULL)
  {
    *head_ref = new_node(a->data);
    head_ref = &(*head_ref)->next;
    suma+=a->data;
    a=a->next;
  }
  while(b!=NULL)
  {
    *head_ref = new_node(b->data);
    head_ref = &(*head_ref)->next;
    sumb+=b->data;
    b=b->next;
  }
  printf("max sum is :%d\n",max(suma,sumb));
  return head;
}
void insertSort(struct node **head_ref)
{
  struct node *head = *head_ref;
  if(head == NULL || head->next==NULL) return;
  struct node *sorted = NULL;
  struct node *next = NULL;
  struct node *curr = head;
  while(curr!=NULL)
  {
    next = curr->next;
    insert_node_in_sorted(&sorted,curr);
    curr = next;
  }
  *head_ref = sorted;
}
