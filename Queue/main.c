#include "queue.h"
#include <stdio.h>
#if 0
int main()
{
  struct Queue *queue = createQueue(4);
  enqueue(queue,1);
  enqueue(queue,2);
  enqueue(queue,3);
  enqueue(queue,4);
  dequeue(queue);
  enqueue(queue,5);
  while(!isEmpty(queue))
  {
    printf(" front:%d rear:%d elem:%d\n ",queue->front,queue->rear,dequeue(queue));
  }
}
#endif
#if 0
int main()
{
  struct queue *queue = queue_create();
  queue_enqueue(queue,1);
  queue_enqueue(queue,2);
  queue_enqueue(queue,3);
  queue_enqueue(queue,4);
  queue_dequeue(queue);
  queue_enqueue(queue,5);
  while(!queue_isEmpty(queue))
  {
    printf(" %d ",queue_dequeue(queue));
  }
}
#endif
#if 1
int main()
{
  int arr[] = {8,1,7,6,0};
  int size = sizeof(arr)/sizeof(arr[0]);
  if(findMaxMultupleOf3(arr,size)==0)
    printf("not possible");
  return 0;
}
#endif
