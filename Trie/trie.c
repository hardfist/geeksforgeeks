#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ALPHABET_SIZE (26)
#define INDEX(c) ((int)c - (int)'a')
typedef struct trie_node
{
  int value;
  bool is_valid;
  struct trie_node * children[ALPHABET_SIZE];
}trie_node_t;
typedef struct trie
{
  trie_node_t *root;
}trie_t;
trie_node_t *trie_node_create()
{
  trie_node_t *new_node =(trie_node_t*)malloc(sizeof(*new_node));
  if(new_node)
  {
    new_node->value = 0;
    new_node->is_valid = false;
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
      new_node->children[i] = NULL;
    }
  }
  return new_node;
}
trie_t* trie_create()
{
  trie_t * t = (trie_t*)malloc(sizeof(*t));
  if(t)
  {
    t->root =trie_node_create();
  }
  return t;
}
bool trie_insert(trie_t *trie,const char *key,int value)
{
  trie_node_t **curr_ref = &(trie->root);
  for(int i=0;key[i];i++)
  {
    curr_ref = &((*curr_ref)->children[INDEX(key[i])]);
    if(*curr_ref == NULL)
    {
      *curr_ref = trie_node_create();
    }
  }
  (*curr_ref)->value = value;
  if(!(*curr_ref)->is_valid)
  {
    (*curr_ref)->is_valid = true;
    return true;
  }
  else
  {
    return false;
  }
}
int trie_search(trie_t *trie,const char *key)
{
  trie_node_t* curr = trie->root;
  for(int i=0;key[i];i++)
  {
    if(!curr) return 0;
    curr = curr->children[INDEX(key[i])];
  }
  if(!curr || !curr->is_valid)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
int main()
{
  char keys[][8] = {"she", "sells", "sea", "shore", "the","shell", "by", "sheer"};
  char output[][32]={"Not present in trie","Present in trie"};
  const int n = sizeof(keys)/sizeof(keys[0]);
  trie_t *trie = trie_create();
  for(int i = 0; i < n; i++)
  {
    trie_insert(trie, keys[i],i);
  }
  // Search for different keys
  printf("%s --- %s\n", "the", output[trie_search(trie, "the")] );
  printf("%s --- %s\n", "these", output[trie_search(trie, "these")] );
  printf("%s --- %s\n", "their", output[trie_search(trie, "their")] );
  printf("%s --- %s\n", "thaw", output[trie_search(trie, "thaw")] );
}
