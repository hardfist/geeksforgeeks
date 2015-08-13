#ifndef _STACK_H
#define _STACK_H
#include <stdbool.h>
// stack operation
struct stack
{
  int top;
  unsigned capacity;
  int *array;
};
struct twoStack
{
  int *arr;
  int size;
  int top1;
  int top2;
};
struct minStack
{
  struct stack *min;
  struct stack *stack;
};
struct node
{
  int data;
  struct node *prev;
  struct node *next;
};
struct midStack
{
  struct node *head;
  struct node *mid;
  int count;
};
// API for midStack
struct midStack *midStack_create();
void midStack_push(struct midStack *stack,int data);
int midStack_pop(struct midStack *stack);
int findMiddle(struct midStack *stack);
// API for twoStack
bool twoStack_isFull(struct twoStack *stack);
bool twoStack_isEmpty(struct twoStack *stack,int id);
void twoStack_push(struct twoStack *stack,int elem,int id);
int twoStack_pop(struct twoStack *stack,int id);
struct twoStack * createTwoStack(int capacity);
// API for stack
struct stack *createStack(unsigned capacity);
bool isEmpty(struct stack *stk);
bool isFull();
int peek();
int pop();
void push(struct stack *stk,int item);
void print(struct stack *stk);
// api for min_stack
struct minStack* minStack_create(int capacity);
void minStack_push(struct minStack *stack,int elem);
int minStack_pop(struct minStack *stack);
bool minStack_isFull(struct minStack *stack);
bool minStack_isEmpty(struct minStack *stack);
int minStack_peek(struct minStack *stack);
int minStack_getMin(struct minStack *stack);
// problem
bool infixToPostfix(char* exp);
int evaluatePostfix(char *exp);
void reverse(char str[]);
bool areParenthesisBalanced(char exp[]);
void printNextGreaterElement(int a[],int n);
void reverseStack(struct stack *stack);
void calculateSpan(int price[],int n,int span[]);
#endif
