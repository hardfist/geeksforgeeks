#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "stack.h"
#define min(a,b) ( (a) < (b) ? (a) : (b))
struct stack* createStack(unsigned capacity)
{
  struct stack *stack = (struct stack*)malloc(sizeof(struct stack));
  if(!stack)
  {
    return NULL;
  }
  stack->capacity = capacity;
  stack->top = 0;
  stack->array = (int*)malloc(stack->capacity*sizeof(int));
  return stack;
}
void print(struct stack *stack)
{
  for(int i=stack->top-1;i>=0;i--)
  {
    printf(" %d ",stack->array[i]);
  }
}
bool isFull(struct stack *stack)
{
  return stack->top == stack->capacity;
}
bool isEmpty(struct stack *stack)
{
  return stack->top == 0;
}
void push(struct stack *stack,int item)
{
  assert(!isFull(stack));
  stack->array[stack->top++]=item;
}
int pop(struct stack *stack)
{
  assert(!isEmpty(stack));
  return stack->array[--stack->top];
}
int peek(struct stack *stack)
{
  assert(!isEmpty(stack));
  return stack->array[stack->top-1];
}
bool isOperand(char ch)
{
  return isalpha(ch) || isdigit(ch);
}
int Prec(char ch)
{
  switch(ch)
  {
    case '+' : case '-':
      return 1;
    case '*' : case '/':
      return 2;
    case '^':
      return 3;
    default:
      return -1;
  }
}
bool infixToPostfix(char *exp)
{
  struct stack *stack = createStack(strlen(exp));
  if(!stack) return false;
  int k=0;
  for(int i=0;exp[i]!='\0';i++)
  {
    if(isOperand(exp[i]))
    {
      exp[k++]=exp[i];
    }
    else if(exp[i] == '(')
    {
      push(stack,exp[i]);
    }
    else if(exp[i] == ')')
    {
      while(!isEmpty(stack) && peek(stack)!='!')
      {
        exp[k++] = pop(stack);
      }
      if(isEmpty(stack) || peek(stack)!='(')
      {
        return false;
      }
      else
      {
        pop(stack);
      }
    }
    else
    {
      while(!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
      {
        exp[k++]=pop(stack);
      }
      push(stack,exp[i]);
    }
  }
  while(!isEmpty(stack))
  {
    exp[k++] = pop(stack);
  }
  exp[k++]='\0';
  return true;
}
int evaluatePostfix(char *exp)
{
  struct stack *stack = createStack(strlen(exp));
  if(!stack) return -1;
  for(int i=0;exp[i]!='\0';i++)
  {
    if(isdigit(exp[i]))
    {
      push(stack,exp[i]-'0');
    }
    else
    {
      int val1 = pop(stack);
      int val2 = pop(stack);
      switch(exp[i])
      {
        case '+': push(stack,val2+val1);break;
        case '-': push(stack,val2-val1);break;
        case '*': push(stack,val2*val1);break;
        case '/': push(stack,val2/val1);break;
      }
    }
  }
  return pop(stack);
}
void reverse(char str[])
{
  struct stack *stack = createStack(strlen(str));
  if(!stack)
  {
    assert(0);
  }
  for(int i=0;str[i];i++)
  {
    push(stack,str[i]);
  }
  int i=0;
  while(!isEmpty(stack))
  {
    str[i++]=pop(stack);
  }
  str[i]='\0';
}
struct twoStack *createTwoStack(int capacity)
{
  // [0,top1) [top2,n)
  struct twoStack *stack = malloc(sizeof(*stack));
  stack->size = capacity;
  stack->top1 = 0;
  stack->top2 = capacity;
  stack->arr = (int*)malloc(sizeof(int)*capacity);
  return stack;
}
bool twoStack_isFull(struct twoStack *stack)
{
  return stack->top1 == stack->top2;
}
bool twoStack_isEmpty(struct twoStack* stack,int id)
{
  assert(stack && (id ==1 || id == 2));
  if(id == 1)
  {
    return stack->top1 == 0;
  }
  else
  {
    return stack->top2 == stack->size;
  }
}
void twoStack_push(struct twoStack *stack,int elem,int id)
{
  assert(!twoStack_isFull(stack) && (id == 1 || id == 2));
  if(id == 1)
  {
    stack->arr[stack->top1++] = elem;
  }
  else
  {
    stack->arr[--stack->top2]=elem;
  }
}
int twoStack_pop(struct twoStack *stack,int id)
{
  assert((id == 1 || id == 2) && !twoStack_isEmpty(stack,id));
  if(id == 1)
  {
    return stack->arr[--stack->top1];
  }
  else
  {
    return stack->arr[stack->top2++];
  } 
}
bool paris(char left,char right)
{
  return (left == '(' && right == ')') || (left == '[' && right == ']') ||(left == '{' && right == '}');
}
bool areParenthesisBalanced(char exp[])
{
  struct stack *stack = createStack(strlen(exp));
  assert(stack);
  for(int i=0;exp[i];i++)
  {
    if(exp[i] == '{'|| exp[i] == '('|| exp[i] == '[')
    {
      push(stack,exp[i]);
    }
    else if(exp[i] == '}' || exp[i] == ']'|| exp[i] ==')')
    {
      if(!isEmpty(stack) &&paris(peek(stack),exp[i]))
      {
        pop(stack);
      }
      else
      {
        return false;
      }
    }
    else
    {
    }
  }
  return isEmpty(stack);
}
void printNextGreaterElement(int a[],int n)
{
  struct stack *stack = createStack(n);
  for(int i=0;i<n;i++)
  {
    if(isEmpty(stack) || peek(stack) > a[i])
    {
      push(stack,a[i]);
    }
    else
    {
      printf("%d nge is %d\n",pop(stack),a[i]);
      push(stack,a[i]);
    }
  }
  while(!isEmpty(stack))
  {
    printf("%d nge is -1\n",pop(stack));
  }
}
void insertAtBottom(struct stack *stack,int elem)
{
  if(isEmpty(stack))
  {
    push(stack,elem);
  }
  else
  {
    int tmp = pop(stack);
    insertAtBottom(stack,elem);
    push(stack,tmp);
  }
}
void reverseStack(struct stack *stack)
{
  if(isEmpty(stack)) return;
  int top = pop(stack);
  reverseStack(stack);
  insertAtBottom(stack,top);
}
void calculateSpan(int price[],int n,int span[])
{
  struct stack *stack = createStack(n);
  for(int i=0;i<n;i++)
  {
    int cnt = 1;
    while(!isEmpty(stack) && price[peek(stack)] < price[i])
    {
      cnt+=span[peek(stack)];
      pop(stack);
    }
    push(stack,i);
    span[i]=cnt;
  }
}
// api for minStack
struct minStack * minStack_create(int capacity)
{
  struct minStack *stack = (struct minStack*)malloc(sizeof(struct minStack));
  stack->min = createStack(capacity);
  stack->stack = createStack(capacity);
  return stack;
}
bool minStack_isEmpty(struct minStack *stack)
{
  return isEmpty(stack->stack);
}
bool minStack_isFull(struct minStack *stack)
{
  return isFull(stack->stack);
}
void minStack_push(struct minStack *stack,int elem)
{
  push(stack->stack,elem);
  push(stack->min,isEmpty(stack->min) ? elem : min(elem,peek(stack->min)));
}
int minStack_pop(struct minStack *stack)
{
  pop(stack->min);
  return pop(stack->stack);
}
int minStack_peek(struct minStack *stack)
{
  return peek(stack->stack);
}
int minStack_getMin(struct minStack *stack)
{
  return peek(stack->min);
}
struct node *make_node(int data)
{
  struct node *node = (struct node*)malloc(sizeof(*node));
  node->next = node->prev = NULL;
  node->data = data;
  return node;
}
struct midStack *midStack_create()
{
  struct midStack *stack = (struct midStack*)malloc(sizeof(*stack));
  stack->count = 0;
  stack->head = NULL;
  stack->mid = NULL;
  return stack;
}
void midStack_push(struct midStack *stack,int data)
{
  struct node *new_node = make_node(data);
  new_node->next = stack->head;
  if(stack->head!=NULL)
  {
    stack->head->prev = new_node;
  }
  stack->head = new_node;
  stack->count++;
  if(stack->count == 1)
  {
    stack->mid = stack->head;
  }
  else if(stack->count%2!=0)
  {
    stack->mid=stack->mid->prev;
  }
}
int midStack_pop(struct midStack *stack)
{
  struct node *head = stack->head;
  stack->head = head->next;
  int item = head->data;
  if(stack->head == NULL)
  {
    stack->head->prev = NULL;
  }
  stack->count--;
  if(stack->count%2==0 && stack->mid!=NULL)
  {
    stack->mid = stack->mid->next;
  }
  free(head);
  return item;
}
int findMiddle(struct midStack *stack)
{
  return stack->mid->data;
}
