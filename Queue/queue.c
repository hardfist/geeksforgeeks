#include "queue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "deque.h"
struct Queue *createQueue(int capacity)
{
  struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
  queue->capacity = capacity;
  queue->front = queue->rear = 0;
  queue->size = 0;
  queue->arr = (int*)malloc(sizeof(int)*capacity);
  return queue;
};
bool isFull(struct Queue *queue)
{
  return queue->size == queue->capacity;
}
bool isEmpty(struct Queue *queue)
{
  return queue->size == 0;
}
void enqueue(struct Queue *queue,int elem)
{
  assert(!isFull(queue));
  queue->arr[queue->rear++]=elem;
  queue->size++;
  if(queue->rear == queue->capacity)
  {
    queue->rear = 0;
  }
}
int dequeue(struct Queue *queue)
{
  assert(!isEmpty(queue));
  int item = queue->arr[queue->front++];
  queue->size--;
  if(queue->front == queue->capacity)
  {
    queue->front = 0;
  }
  return item;
}
// api for list_queue
struct queue* queue_create()
{
  struct queue * queue = (struct queue*)malloc(sizeof(*queue));
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  return queue;
}
bool queue_isEmpty(struct queue *queue)
{
  return queue->size == 0;
}
void queue_enqueue(struct queue *queue,int data)
{
  struct node *new_node = (struct node*)malloc(sizeof(*new_node));
  new_node->data = data;
  new_node->next = NULL;
  queue->size++;
  if(queue->head == NULL)
  {
    queue->head = new_node;
    queue->tail = new_node;
  }
  else
  {
    queue->tail->next = new_node;
    queue->tail = new_node;
  }
}
int queue_dequeue(struct queue *queue)
{
  assert(!queue_isEmpty(queue));
  queue->size--;
  struct node *head = queue->head;
  int item = head->data;
  queue->head = head->next;
  if(queue->head == NULL)
  {
    queue->tail = NULL;
  }
  free(head);
  return item;
}
int compare(const void *a,const void *b)
{
  return *(int*)a > *(int*)b;
}
int compareDesc(const void *a,const void *b)
{
  return *(int*)a < *(int*)b;
}
void printArr(int arr[],int n)
{
  for(int i=0;i<n;i++)
  {
    printf(" %d ",arr[i]);
  }
  puts("");
}
void populateAux(int aux[],struct Queue* queue0,struct Queue* queue1,struct Queue* queue2,int *top)
{
  while(!isEmpty(queue0))
  {
    aux[(*top)++] = dequeue(queue0);
  }
  while(!isEmpty(queue1))
  {
    aux[(*top)++] = dequeue(queue1);
  }
  while(!isEmpty(queue2))
  {
    aux[(*top)++] = dequeue(queue2);
  }
}
int findMaxMultupleOf3(int arr[],int size)
{
  qsort(arr,size,sizeof(int),compare);

  struct Queue *queue0 = createQueue(size);
  struct Queue *queue1 = createQueue(size);
  struct Queue *queue2 = createQueue(size);

  int sum = 0;
  for(int i=0;i<size;i++)
  {
    sum+=arr[i];
    if(arr[i]%3 == 0)
    {
      enqueue(queue0,arr[i]);
    }
    else if(arr[i]%3 == 1)
    {
      enqueue(queue1,arr[i]);
    }
    else
    {
      enqueue(queue2,arr[i]);
    }
  }
  if((sum%3) == 1)
  {
    if(!isEmpty(queue1))
    {
      dequeue(queue1);
    }
    else
    {
      if(!isEmpty(queue2))
      {
        dequeue(queue2);
      }
      else
      {
        return 0;
      }
      if(!isEmpty(queue2))
      {
        dequeue(queue2);
      }
      else
      {
        return 0;
      }
    }
  }
  else if ((sum%3)==2)
  {
    if(!isEmpty(queue2))
    {
      dequeue(queue2);
    }
    else
    {
      if(!isEmpty(queue1))
      {
        dequeue(queue1);
      }
      else
      {
        return 0;
      }
      if(!isEmpty(queue1))
      {
        dequeue(queue1);
      }
      else
      {
        return 0;
      }
    }
  }
  int aux[size],top=0;
  populateAux(aux,queue0,queue1,queue2,&top);
  qsort(aux,top,sizeof(int),compareDesc);
  printArr(aux,top);
  return top;
}
void printKMax(int arr[],int n,int k)
{
  std::deque deq(k);
  for(int i=0;i<k;i++)
  {
    while(!deq.empty() && arr[i] >=arr[deq.back()])
    {
      deq.pop_back();
    }
    deq.push_back(i);
  }
  for(int i=k;i<n;i++)
  {
    cout<<arr[deq.front()]<<" ";
    while((!deq.empty()) && deq.front()<=i-k)
    {
      deq.pop_front();
    }
    while((!deq.empty()) && arr[i] >= arr[deq.back()])
    {
      deq.pop_back();
    }
  }
  cout<<arr[deq.front()];
}
