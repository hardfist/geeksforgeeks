#include <iostream>
using namespace std;
class BTreeNode
{
  int *keys;
  int t;
  BTreeNode **C;
  int n;
  bool leaf;
 public:
  BTreeNode(int _t,bool _leaf);
  void traverse();
  void insertNonFull(int k);
  void splitChild(int i,BTreeNode *y);
  BTreeNode *search(int k);
  friend class BTree;
};
class BTreeNode
{
  BTreeNode *root;
  int t;
 public:
  BTree(int _t)
  {
    root = NULL;
    t = _t;
  }
  void traverse()
  {
    if(root!=NULL)
    {
      root->traverse();
    }
  }
  BTreeNode* search(int k)
  {
    return root == NULL ? NULL : root->search();
  }
  void insert(int k);
};
BTreeNode::BTreeNode(int _t,bool _leaf)
{
  t = _t;
  leaf = _leaf;
  keys = new int[2*t-1];
  C = new BTreeNode* [2*t];
  n = 0;
}
void BTreeNode::traverse()
{
  int i;
  for(i=0;i<n;i++)
  {
    if(leaf == false)
    {
      C[i]->traverse();
      cout<<" "<<keys[i];
    }
  }
  if(leaf == false)
  {
    C[i]->traverse();
  }   
}
BTreeNode *BTreeNode::search(int k)
{
  int i = 0;
  while(i<n && k>keys[i]) i++;
  // keys[i]>=k
  if(keys[i] == k)
  {
    return this;
  }
  if(leaf == true)
  {
    return NULL;
  }
  return C[i]->search(k);
}
void BTree::insert(int k)
{
  if(root == NULL)
  {
    root = new BTreeNode(t,true);
    root->keys[0] = k;
    root->n  = 1;
  }
  else
  {
    if(root->n == 2*t-1)
    {
      BTreeNode *s = new BTreeNode(t,false);
      s->C[0] = root;
      s->splitChild(0,root);
    }
  }
}
// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i,BTreeNode *y)
{
  BTreeNode *z = new BTreeNode(y->t,y->leaf);
  z->n = t-1;
  for(int j=0;j<t-1;j++)
  {
    z->keys[j] = y->keys[j+t];
  }
  if(y->leaf = false)
  {
    for(int j=0;j<t;j++)
    {
      z->C[j] = y->C[j+t];
    }
  }
  y->n = t-1;
  for(int j=n;j>=i+1;j--)
  {
    keys[j+1] = keys[j];
  }
  keys[i] = y->keys[t-1];
  n=n+1;
}
int main()
{}
