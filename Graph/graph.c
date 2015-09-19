#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
struct AdjListNode
{
  int dest;
  struct AdjListNode *next;
};
struct AdjList
{
  struct AdjListNode *head;
};
struct Graph
{
  int V;
  struct AdjList* array;
};
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
//A utility function that creates a graph of V vertices
/*
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}
*/
struct Graph* createGraph(int V)
{
  struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->V = V;
  graph->array = (struct AdjList*)malloc(V*sizeof(struct AdjList));
  for(int i=0;i<V;i++)
  {
    graph->array[i].head = NULL;
  }
  return graph;
}

void addEdge(struct Graph* graph,int src,int dest)
{
  struct AdjListNode* newNode = newAdjListNode(dest);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;
  
  /* newNode = newAdjListNode(src); */
  /* newNode->next = graph->array[dest].head; */
  /* graph->array[dest].head = newNode; */
}
void graphdump(struct Graph *graph,int i)
{
  for(struct AdjListNode* curr = graph->array[i].head;curr!=NULL;curr=curr->next)
  {
    printf(" %d ",curr->dest);
  }
}
void printGraph(struct Graph *graph)
{
  for(int v=0;v<graph->V;v++)
  {
    struct AdjListNode* curr = graph->array[v].head;
    printf("\n Adjacency list of vertex %d\n head",v);
    while(curr!=NULL)
    {
      printf("-> %d",curr->dest);
      curr = curr->next;
    }
    puts("");
  }
}
#if 1
// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    //    addEdge(graph, 0, 4);
    // print the adjacency list representation of the above graph
    printGraph(graph);
 
    return 0;
}
#endif
