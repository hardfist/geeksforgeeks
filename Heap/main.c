#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#if 0
int main()
{
  struct MinHeap *h = heap_create(11);
  push(h,3);
  push(h,2);
  push(h,5);
  while(!isEmpty(h))
  {
    printf(" %d ",pop(h));
  }
}
#endif
#if 0
/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, size);
    kLargest(arr,size,3);
}
#endif

#if 0
// Driver program to test above functions
int main()
{
    int k = 3;
    int arr[] = {2, 6, 3, 12, 56, 8};
    int n = sizeof(arr)/sizeof(arr[0]);
    sortK(arr, n, k);
 
    puts("Following is sorted array\n");
    printArray (arr, n);
 
    return 0;
}
#endif
#if 1
int main()
{
  char *v = (char*)malloc(0);
  printf("%p\n",v);
}
#endif

