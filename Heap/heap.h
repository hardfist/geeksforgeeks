#ifndef _HEAP_H
#define _HEAP_H
#include <stdbool.h>
struct MinHeap
{
  int *arr;
  int capacity;
  int size;
};
struct MinHeap* heap_create(int capacity);
bool isFull(struct MinHeap *heap);
bool isEmpty(struct MinHeap *heap);
void push(struct MinHeap *heap,int data);
int pop(struct MinHeap *heap);
int peek(struct MinHeap* heap);
int replacetop(struct MinHeap *heap,int x);
void heapSort(int arr[],int n);
void printArray(int arr[],int n);
void kLargest(int arr[],int n,int k);
void sortK(int arr[],int n,int k);
#endif
