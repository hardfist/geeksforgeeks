#include <stdio.h>
#include <assert.h>
#include <stack>
#include <queue>
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
  struct node *parent;
} node;
struct node* new_node(int key)
{
  node* n = (node*)malloc(sizeof(*n));
  n->key = key;
  n->left = n->right = n->parent = NULL;
  return n;
}
struct node* search(node *r,int key)
{
  while(r!=NULL && r->key != key)
  {
    if(key < r->key)
    {
      r = r->left;
    }
    else
    {
      r = r->right;
    }
  }
  return r;
}
node *min(node *r)
{
  assert(r);
  while(r->left!=NULL)
  {
    r=r->left;
  }
  return r;
}
node *max(node *r)
{
  assert(r);
  while(r->right!=NULL)
  {
    r=r->right;
  }
  return r;
}
node *succ(node *r)
{
  assert(r);
  if(r->right)
  {
    return min(r->right);
  }
  else
  {
    while(r->parent && r->parent->right == r)
    {
      r = r->parent;
    }
    return r->parent;
  }
}
node *pred(node *r)
{
  assert(r);
  if(r->left)
  {
    return max(r->left);
  }
  else
  {
    while(r->parent && r->parent->left == r)
    {
      r = r->parent;
    }
    return r->parent;
  }
}
void insert(node **root_ref,int key)
{
  node *r = *root_ref;
  node *n = new_node(key);
  node *parent = NULL;
  while(r)
  {
    parent = r;
    if(key < r->key)
    {
      r = r->left;
    }
    else
    {
      r=r->right;
    }
  }
  n->parent = parent;
  if(parent == NULL)
  {
    *root_ref = n;
  }
  else if(key < parent->key)
  {
    parent->left = n;
  }
  else
  {
    parent->right = n;
  }
}
void transplant(node** root_ref,node *u,node *v)
{
  if(u->parent == NULL)
  {
    *root_ref = v;
  }
  else if( u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  if(v!=NULL)
  {
    v->parent = u->parent;
  }
}
void remove(node **root_ref,int key)
{
  node *r = *root_ref;
  node *parent = NULL;
  while(r && r->key != key)
  {
    parent = r;
    if(key < r->key)
    {
      r = r->left;
    }
    else
    {
      r = r->right;
    }
  }
  if(r == NULL) return;
  if(r->left == NULL)
  {
    transplant(root_ref,r,r->right);
  }
  else if(r->right == NULL)
  {
    transplant(root_ref,r,r->left);
  }
  else
  {
    node *y = min(r->right);
    if(y->parent!=r)
    {
      transplant(root_ref,y,y->right);
      y->right = r->right;
      y->right->parent = y;
    }
    transplant(root_ref,r,y);
    y->left = r->left;
    y->left->parent =y;
  }
  return ;
}
void inorder(node *r)
{
  std::stack<node*> stk;
  while(r || !stk.empty())
  {
    if(r)
    {
      stk.push(r);
      r = r->left;
    }
    else
    {
      r = stk.top();
      stk.pop();
      printf(" %d ",r->key);
      r = r->right;
    }
  }
}
void level_order(node *r,void (*fun)(node *n))
{
  std::queue<node*> que;
  if(r)
  {
    que.push(r);
  }
  while(!que.empty())
  {
    r = que.front();
    que.pop();
    fun(r);
    if(r->left)
    {
      que.push(r->left);
    }
    if(r->right)
    {
      que.push(r->right);
    }
  }
}
void print_tree_helper(node *r,int indent)
{
  if(r)
  {
    print_tree_helper(r->left,indent+2);
    for(int i=0;i<indent;i++) putchar(' ');
    printf("%d\n",r->key);
    print_tree_helper(r->right,indent+2);
  }
}
void print_tree(node *r)
{
  print_tree_helper(r,0);
}
void inorder_r(node *r,void (*fun)(node *n))
{
  if(r)
  {
    inorder_r(r->left,fun);
    fun(r);
    inorder_r(r->right,fun);
  }
}
void print(node *n)
{
  printf(" %d ",n->key);
}
void print_pred(node *n)
{
  node *t = pred(n);
  if (t==NULL)
  {
    printf("%d pred is null\n ",n->key);
  }
  else
  {
    printf("%d pred is %d\n",n->key,t->key);
  }
}
void print_succ(node *n)
{
  node *t = succ(n);
  if (t==NULL)
  {
    printf("%d succ is null\n",n->key);
  }
  else
  {
    printf("%d succ is %d\n",n->key,t->key);
  }
}

#if 1
int main()
{
  const int n = 20;
  int a[n];
  for(int i=0;i<n;i++)
  {
    a[i] = rand()%100;
  }
  for(int i=0;i<n;i++)
  {
    printf(" %d ",a[i]);
  }
  puts("");
  node* root = NULL;
  for(int i=0;i<n;i++)
  {
    insert(&root,a[i]);
  }
  printf("inorder visit:\n");
  inorder_r(root,print);
  puts("");
  #if 0
  printf("pred:\n");
  inorder_r(root,print_pred);
  puts("");
  printf("succ:\n");
  inorder_r(root,print_succ);
  puts("");
  #endif
  for(int i=0;i<n;i++)
  {
    printf("after delete %d:\n",a[i]);
    remove(&root,a[i]);
    //    print_tree(root);
    inorder_r(root,print);
    puts("");
  }
}
#endif
