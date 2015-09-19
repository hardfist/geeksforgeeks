#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#define MAXLEVEL 6
typedef struct node
{
  int key;
  int value;
  struct node **forward;
}node;
typedef struct skiplist
{
  struct node *header;
}skiplist;
static int randLevel()
{
  return rand()%MAXLEVEL+1;
}
struct node *node_create(int key,int value,int level)
{
  node *new_node = (node*)malloc(sizeof(*new_node));
  new_node->key = key;
  new_node->value = value;
  new_node->forward = (node**)malloc(sizeof(node*)*level);
  for(int i=0;i<level;i++)
  {
    new_node->forward[i] = NULL;
  }
  return new_node;
}
struct skiplist *skiplist_create()
{
  struct skiplist *list = (struct skiplist*)malloc(sizeof(*list));
  list->header = node_create(INT_MAX,INT_MAX,MAXLEVEL);
  for(int i=0;i<MAXLEVEL;i++)
  {
    list->header->forward[i] = list->header;
  }
  return list;
}
void getUpdate(struct skiplist* list,int key,struct node** update)
{
  struct node *x = list->header;
  for(int i=MAXLEVEL-1;i>=0;i--)
  {
    while(x->forward[i]->key < key)
    {
      x = x->forward[i];
    }
    update[i] = x;
  }
}
bool skiplist_insert(struct skiplist* list,int key,int value)
{
  struct node * update[MAXLEVEL];
  getUpdate(list,key,update);
  struct node *x = update[0]->forward[0];
  if(x->key == key)
  {
    x->value = value;
    return false;
  }
  else
  {
    int level = randLevel();
    struct node *new_node = node_create(key,value,level);
    for(int i=0;i<level;i++)
    {
      new_node->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = new_node;
    }
    return true;
  }
}
struct node *skiplist_search(struct skiplist* list,int key)
{
  struct node *update[MAXLEVEL];
  getUpdate(list,key,update);
  struct node *x = update[0]->forward[0];
  if(x->key == key)
  {
    return x;
  }
  else
  {
    return false;
  }
}
bool skiplist_delete(struct skiplist* list,int key)
{
  struct node *update[MAXLEVEL];
  getUpdate(list,key,update);
  struct node *x = update[0]->forward[0];
  if(x->key !=key)
  {
    return false;
  }
  else
  {
    for(int i=0;i<MAXLEVEL;i++)
    {
      if(update[i]->forward[i] == x)
      {
        update[i]->forward[i] = x->forward[i];
      }
    }
    free(x);
    return true;
  }
}
void skiplist_dump(struct skiplist *list)
{
  for(int i=MAXLEVEL-1;i>=0;i--)
  {
    printf("level %d:\t",i);
    for(struct node *curr = list->header->forward[i];curr!=list->header;curr=curr->forward[i])
    {
      printf("(%d,%d)->",curr->key,curr->value);
    }
    puts("");
  }
  puts("\n");
}
int main()
{
  int arr[] = {1,2,3,4,5,6,7,8,9};
  const int n = sizeof(arr)/sizeof(arr[0]);
  struct skiplist *list = skiplist_create();
  printf("insert...........\n");
  for(int i=0;i<n;i++)
  {
    skiplist_insert(list,arr[i],arr[i]);
  }
  printf("search............\n");
  int keys[]={1,3,5,7,9,11};
  for(int i=0;i<sizeof(keys)/sizeof(keys[0]);i++)
  {
    node *x = skiplist_search(list,keys[i]);
    if(x!=NULL)
    {
      printf("key = %d, value = %d\n",keys[i],x->value);
    }
    else
    {
      printf("key = %d,not found\n",keys[i]);
    }
  }
  printf("beforedelete............\n");
  skiplist_dump(list);
  printf("after_delete.............\n");
  for(int i=0;i<n;i++)
  {
    skiplist_delete(list,arr[i]);
    skiplist_dump(list);
  }
}

