#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
typedef struct node
{
  int key;
  int value;
  struct node *next;
}node;
typedef struct skiplist
{
  node *header;
}skiplist;
skiplist* skiplist_create() 
{
  skiplist* list = (struct skiplist*)malloc(sizeof(struct skiplist));
  list->header = (struct node*)malloc(sizeof(struct node));
  list->header->key = INT_MAX;
  list->header->value = INT_MAX;
  list->header->next =list->header;
  return list;
}
bool skiplist_insert(skiplist *list,int key,int value)
{
  struct node *head = list->header;
  while(head->next->key < key)
  {
    head = head->next;
  }
  if(head->next->key == key)
  {
    return false;
  }
  node *new_node = (node*)malloc(sizeof(struct node));
  new_node->key = key;
  new_node->value = value;
  new_node->next = head->next;
  head->next = new_node;
  return true;
}
struct node *skiplist_search(skiplist *list,int key)
{
  for(struct node *curr = list->header->next;curr!=list->header;curr = curr->next)
  {
    if(curr->key == key)
    {
      return curr;
    }
  }
  return NULL;
}
bool skiplist_delete(struct skiplist *list,int key)
{
  struct node *prev = list->header;
  while(prev->next->key < key)
  {
    prev = prev->next;
  }
  if(prev->next->key == key)
  {
    struct node *next = prev->next;
    prev->next = next->next;
    free(next);
    return true;
  }
  else
  {
    return false;
  }
}
void skiplist_dump(struct skiplist *list)
{
  for(struct node *curr = list->header->next;curr!=list->header;curr = curr->next)
  {
    printf("(%d:%d)->",curr->key,curr->value);
  }
  puts("");
}
int main()
{
    int arr[] = {3, 6, 9, 2, 11, 1, 4}, i;
    skiplist *list = skiplist_create();
    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        skiplist_insert(list, arr[i], arr[i]);
    }
    skiplist_dump(list);

    printf("Search:--------------------\n");
    int keys[] = {3, 4, 7, 10, 111};

    for (i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        node *x = skiplist_search(list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not fuound\n", keys[i]);
        }
    }

    printf("Search:--------------------\n");
    skiplist_delete(list, 3);
    skiplist_delete(list, 9);
    skiplist_dump(list);

    return 0;
}
