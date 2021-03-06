#include <stdio.h>
#include "stack.h"
#if 0
int main()
{
  struct stack *stack = createStack(100);
  push(stack,10);
  push(stack,20);
  push(stack,30);

  printf("%d popped from stack\n",pop(stack));
  printf("Top item is %d\n",peek(stack));
  return 0;
}
#endif
#if 0
int main()
{
  char exp[] = "1+2*3-4";
  printf("%s\n",exp);
  reverse(exp);
  printf("%s\n",exp);
}
#endif

#if 0
int main()
{
  struct twoStack *stack = createTwoStack(5);
  twoStack_push(stack,5,1);
  twoStack_push(stack,10,2);
  twoStack_push(stack,15,2);
  twoStack_push(stack,11,1);
  twoStack_push(stack,7,2);
  //  twoStack_push(stack,8,3); // overflow test
  printf("Popped element from stack1 is \n");
  while(!twoStack_isEmpty(stack,1))
  {
    printf(" %d ",twoStack_pop(stack,1));
  }
  puts("");
  printf("Popped element from stack2 is \n");
  while(!twoStack_isEmpty(stack,2))
  {
    printf(" %d ",twoStack_pop(stack,2));
  }
  puts("");
}
#endif
#if 0
/* UTILITY FUNCTIONS */
/*driver program to test above functions*/
int main()
{
  char exp[100] = "{()}[]";
  if(areParenthesisBalanced(exp))
    printf("\n Balanced ");
  else
    printf("\n Not Balanced ");  \
  getchar();
}    
#endif
/* #if 1 */
/* int main() */
/* { */
/*   int arr[] = {11,13,21,3}; */
/*   int n = sizeof(arr)/sizeof(arr[0]); */
/*   printNextGreaterElement(arr,n); */
/*   getchar(); */
/*   return 0; */
/* } */
/* #endif */
#if 0
/* Driveer program to test above functions */
int main()
{
  struct stack* s =createStack(4);
  push(s, 4);
  push(s, 3);
  push(s, 2);
  push(s, 1);  
 
  printf("\n Original Stack ");
  print(s);
  reverseStack(s);
  printf("\n Reversed Stack ");  
  print(s);
  getchar();
}    
#endif
#if 0
// Driver program to test above function
static void printArray(int arr[],int n)
{
  for(int i=0;i<n;i++)
  {
    printf(" %d ",arr[i]);
  }
}
int main()
{
    int price[] = {10, 4, 5, 90, 120, 80};
    int n = sizeof(price)/sizeof(price[0]);
    int S[n];
 
    // Fill the span values in array S[]
    calculateSpan(price, n, S);
 
    // print the calculated span values
    printArray(S, n);
 
    return 0;
}
#endif
#if 0
/* Driver program to test SpecialStack methods */
int main()
{
  struct minStack *stack = minStack_create(4);
  minStack_push(stack,10);
  minStack_push(stack,20);
  minStack_push(stack,30);
  printf(" %d ",minStack_getMin(stack));
  minStack_push(stack,5);
  printf(" %d ",minStack_getMin(stack));
  return 0;
}
#endif
#if 1
// Driver program to test functions of myStack
int main()
{
    /* Let us create a stack using push() operation*/
  struct midStack *ms = midStack_create();
    midStack_push(ms, 11);
    midStack_push(ms, 22);
    midStack_push(ms, 33);
    midStack_push(ms, 44);
    midStack_push(ms, 55);
    midStack_push(ms, 66);
    midStack_push(ms, 77);
 
    printf("Item midStack_popped is %d\n", midStack_pop(ms));
    printf("Item midStack_popped is %d\n", midStack_pop(ms));
    printf("Middle Element is %d\n", findMiddle(ms));
    return 0;
}
#endif
