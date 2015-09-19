#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdbool.h>
struct Queue
{
  int front,rear;
  int size;
  int *arr;
  int capacity;
};
struct Queue *createQueue(int capacity);
bool isFull(struct Queue *queue);
bool isEmpty(struct Queue *queue);
void enqueue(struct Queue *queue,int elem);
int dequeue(struct Queue *queue);
struct node
{
  int data;
  struct node *next;
};
struct queue
{
  struct node *head;
  struct node *tail;
  int size;
};
struct queue *queue_create();
bool queue_isEmpty(struct queue*);
void queue_enqueue(struct queue*,int);
int queue_dequeue(struct queue*);
int findMaxMultupleOf3(int arr[],int n);
// application
void printKMax(int arr[],int n,int k);
#endif
