#include "heap.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
static int par(int i) { return (i-1)/2;}
static int left(int i) { return 2*i+1;}
static int right(int i) { return 2*i+2;}
static void swap(int *x,int *y) { int tmp = *x;*x = *y;*y = tmp;}
static void sink(struct MinHeap *heap,int i)
{
  int *arr = heap->arr;
  int size = heap->size;
  while(i<size)
  {
    int min = i;
    if(left(i) < size && arr[left(i)]<arr[i])
    {
      min = left(i);
    }
    if(right(i) < size && arr[right(i)] < arr[min])
    {
      min = right(i);
    }
    if( min !=i)
    {
      swap(&arr[i],&arr[min]);
      i = min;
    }
    else
    {
      break;
    }
  }
}
void swim(struct MinHeap *heap,int i)
{
  int *arr =heap->arr;
  while(i!=0)
  {
    if(arr[par(i)]>arr[i])
    {
      swap(&arr[par(i)],&arr[i]);
      i = par(i);
    }
    else
    {
      break;
    }
  }
}
struct MinHeap *heap_create(int capacity)
{
  struct MinHeap *heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
  heap->size = 0;
  heap->capacity = capacity;
  heap->arr = (int*)malloc(sizeof(int)*capacity);
  return heap;
}
void push(struct MinHeap *heap,int data)
{
  assert(!isFull(heap));
  heap->arr[heap->size++] = data;
  swim(heap,heap->size-1);
}
int peek(struct MinHeap *heap)
{
  assert(!isEmpty(heap));
  return heap->arr[0];
}
int pop(struct MinHeap *heap)
{
  int item = heap->arr[0];
  swap(&heap->arr[0],&heap->arr[--heap->size]);
  sink(heap,0);
  return item;
}
bool isEmpty(struct MinHeap *heap)
{
  return heap->size == 0;
}
bool isFull(struct MinHeap *heap)
{
  return heap->size == heap->capacity;
}
void heapSort(int arr[],int n)
{
  struct MinHeap* heap = heap_create(n);
  for(int i=0;i<n;i++)
  {
    push(heap,arr[i]);
  }
  int i=0;
  while(!isEmpty(heap))
  {
    arr[i++]=pop(heap);
  }
}
void printArray(int a[],int n)
{
  for(int i=0;i<n;i++)
  {
    printf(" %d ",a[i]);
  }
  puts("");
}
void kLargest(int a[],int n,int k)
{
  struct MinHeap *heap = heap_create(k);
  for(int i=0;i<k;i++)
  {
    push(heap,a[i]);
  }
  for(int i=k;i<n;i++)
  {
    if(a[i] > peek(heap))
    {
      pop(heap);
      push(heap,a[i]);
    }
  }
  while(!isEmpty(heap))
  {
    printf(" %d ",pop(heap));
  }
}
int replacetop(struct MinHeap *heap,int x)
{
  int root = pop(heap);
  push(heap,x);
  return root;
}
void sortK(int a[],int n,int k)
{
  struct MinHeap *heap = heap_create(k+1);
  for(int i=0;i<k+1;i++)
  {
    push(heap,a[i]);
  }
  for(int i=k+1,ti=0;ti<n;i++,ti++)
  {
    if(i<n)
    {
      a[ti] = replacetop(heap,a[i]);
    }
    else
    {
      a[ti] = pop(heap);
    }
  }
}
