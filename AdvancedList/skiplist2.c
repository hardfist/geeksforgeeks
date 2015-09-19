#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#define MAXLEVEL 5
typedef struct node
{
  int key;
  int value;
  struct node **forward;
}node;
typedef struct skiplist
{
  //  int level;
  struct node *header;
}skiplist;
static int randLevel()
{
  int level = 1;
  while(rand()%2!=0 && level < MAXLEVEL)
  {
    level++;
  }
  return level;
}
struct node *node_create(int key,int value,int level)
{
  struct node *new_node = (struct node*)malloc(sizeof(struct node));
  new_node->key = key;
  new_node->value = value;
  new_node->forward = (struct node**)malloc(sizeof(struct node*)*level);
  for(int i=0;i<level;i++)
  {
    new_node->forward[i] = NULL;
  }
  return new_node;
}
struct skiplist * skiplist_create()
{
  struct skiplist *list = (struct skiplist*)malloc(sizeof(struct skiplist));
  list->header = node_create(INT_MAX,INT_MAX,MAXLEVEL);
  for(int i=0;i<MAXLEVEL;i++)
  {
    list->header->forward[i] = list->header;
  }
  return list;
}
void skiplist_insert(struct skiplist *list,int key,int value)
{
  struct node *x = list->header;
  struct node * update[MAXLEVEL];
  for(int i=MAXLEVEL-1;i>=0;i--)
  {
    while(x->forward[i]->key < key)
    {
      x=x->forward[i];
    }
    update[i]=x;
  }
  if(x->forward[0]->key == key)
  {
    x->forward[0]->value = value;
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
  }
}
struct node* skiplist_search(struct skiplist *list,int key)
{
  struct node *x = list->header;
  for(int i=MAXLEVEL-1;i>=0;i--)
  {
    while(x->forward[i]->key<key)
    {
      x = x->forward[i];
    }
  }
  if(x->forward[0]->key == key)
  {
    return x->forward[0];
  }
  else
  {
    return NULL;
  }
}
bool skiplist_delete(struct skiplist *list,int key)
{
  struct node *x = list->header;
  struct node *update[MAXLEVEL];
  for(int i=MAXLEVEL-1;i>=0;i--)
  {
    while(x->forward[i]->key < key)
    {
      x = x->forward[i];
    }
    update[i] = x;
  }
  x = x->forward[0];
  if(x->key !=key)
  {
    return false;
  }
  else
  {
    for(int i=MAXLEVEL-1;i>=0;i--)
    {
      if(update[i]->forward[i]==x)
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
    printf("level %d :\t",i);
    for(struct node *curr = list->header->forward[i];curr!=list->header;curr=curr->forward[i])
    {
      printf("(%d:%d)->",curr->key,curr->value);
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
