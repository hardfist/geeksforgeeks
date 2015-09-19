#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define NOT_A_CHAR (-1)
#define MAXLENGTH 100
typedef struct trie_node
{
  int key;
  bool is_valid;
  struct trie_node *lch;
  struct trie_node *mid;
  struct trie_node *rch;
}trie_node_t;
typedef struct trie
{
  trie_node_t *root;
}trie_t;
trie_node_t* node_create()
{
  trie_node_t* node = (trie_node_t*)malloc(sizeof(*node));
  if(node)
  {
    node->key = NOT_A_CHAR;
    node->is_valid = false;
    node->lch = NULL;
    node->rch = NULL;
    node->mid = NULL;
  }
  return node;
}
trie_t* trie_create()
{
  trie_t *trie = (trie_t*)malloc(sizeof(*trie));
  if(trie)
  {
    trie->root = NULL;
  }
  return trie;
}
bool trie_insert(trie_t *trie,const char *key)
{
  trie_node_t **cur_ref = &(trie->root);
  for(int i=0;key[i]!='\0';)
  {
    if(*cur_ref == NULL)
    {
      *cur_ref = node_create();
      (*cur_ref)->key = key[i];
    }
    if( key[i] < (*cur_ref)->key)
    {
      cur_ref = &(*cur_ref)->lch;
    }
    else if( key[i] > (*cur_ref)->key)
    {
      cur_ref = &(*cur_ref)->rch;
    }
    else
    {
      if(key[i+1]=='\0')
      {
        if((*cur_ref)->is_valid == true)
        {
          return false;
        }
        else
        {
          (*cur_ref)->is_valid = true;
          return true;
        }
      }
      cur_ref = &(*cur_ref)->mid;
      i++;
    }
  }
  assert(0);
  return false;
}
trie_node_t *trie_search(trie_t *trie,const char *key)
{
  trie_node_t *curr = trie->root;
  for(int i=0;key[i]!='\0';)
  {
    if(curr==NULL) return NULL;
    if(key[i] < curr->key)
    {
      curr = curr->lch;
    }
    else if(key[i] > curr->key)
    {
      curr = curr->rch;
    }
    else
    {
      if(key[i+1]=='\0' && curr->is_valid)
      {
        return curr;
      }
      curr = curr->mid;
      i++;
    }
  }
  return NULL;
}
bool trie_delete(trie_t *trie,const char *key)
{
  trie_node_t *t = trie_search(trie,key);
  if(t==NULL|| !t->is_valid)
  {
    return false;
  }
  else
  {
    t->is_valid = false;
    return true;
  }
}
void visit(trie_node_t *trie,char str[],int k)
{
  if(trie)
  {
    if(trie->is_valid)
    {
      str[k]=trie->key;
      for(int i=0;i<=k;i++)
      {
        putchar(str[i]);
      }
      printf(" ");
    }
    visit(trie->lch,str,k);
    visit(trie->rch,str,k);
    str[k]=trie->key;
    visit(trie->mid,str,k+1);
  }
}
int long_prefix(trie_t *trie,const char *key)
{
  trie_node_t *x = trie->root;
  int last = 0;
  for(int i=0;key[i];)
  {
    if(x==NULL) break;
    if(x->is_valid)
    {
      last = i;
    }
    if(key[i] < x->key)
    {
      x = x->lch;
    }
    else if(key[i] > x->key)
    {
      x = x->rch;
    }
    else
    {
      x = x->mid;
      i++;
    }
  }
  return last;
}
void trie_visit(trie_t *trie)
{
  char str[MAXLENGTH+1];
  visit(trie->root,str,0);
}
void findUniqueRows(int row,int col,int M[row][col])
{
  trie_t *trie = trie_create();
  char mat[row][col+1];
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      mat[i][j] = M[i][j] +'0';
    }
    mat[i][col] = '\0';
  }
  for(int i=0;i<row;i++)
  {
    if(trie_insert(trie,mat[i]))
    {
      puts(mat[i]);
    }
  }
}
void printStr(char *str,int k)
{
  for(int i=0;i<k;i++)
  {
    putchar(str[i]);
  }
  printf(" ");
}
#if 0
int main()
{
  char keys[][8] = {"are","area","base","cat","cater","basement"};
  const int n = sizeof(keys)/sizeof(keys[0]);
  trie_t *trie = trie_create();
  for(int i = 0; i < n;i++)
  {
    trie_insert(trie, keys[i]);
  }
  char querys[][20]={"caterer","basement","are","arex","basemenxz","xyz"};
  for(int i=0;i<sizeof(querys)/sizeof(querys[0]);i++)
  {
    printf("long_prefix of %s:",querys[i]);
    printStr(querys[i],long_prefix(trie,querys[i]));
    puts("");
  }
  return 0;
}
#endif
#if 1
int main()
{
  int m[][5]={{0,1,0,0,1},
              {1,0,1,1,0},
              {0,1,0,0,1},
              {1,0,1,0,0}
  };
  int row = sizeof(m)/sizeof(m[0]);
  int col = sizeof(m[0])/sizeof(m[0][0]);
  findUniqueRows(row,col,m);
  return 0;
}
#endif
