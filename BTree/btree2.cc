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
  BTreeNode(int _t,bool _leaf)
      :t(_t),leaf(_leaf)
  {
    // invariant
    //    C[0] < keys[0] < C[1] < keys[1]
    keys = new int[2*t-1];
    C = new BTreeNode* [2*t];
    n = 0;
  }
  void traverse()
  {
    int i;
    for(i=0;i<n;i++)
    {
      if(!leaf)
      {
        C[i]->traverse();
      }
      cout << " " << keys[i];
    }
    if(!leaf)
    {
      C[i]->traverse();
    }
  }
  BTreeNode* search(int k)
  {
    int i = 0;
    while(i<n && k > keys[i])
    {
      i++;
    }
    // k>keys[i-1] && k < keys[i] so k in C[i]
    if(leaf) return NULL;
    return C[i]->search(k);
  }
  void insertNonFull(int k)
  {
    int i = n-1;
    // leaf
    if(leaf)
    {
      while(i>=0 && keys[i] > k)
      {
        keys[i+1] = keys[i];
        i--;
      }
      keys[i+1] = k;
      n++;
    }
    else
    {
      while(i>=0 && keys[i]>k)
      {
        i--;
      }
      // keys[i]<=k<keys[i+1] so insert k in C[i+1]
      if(C[i+1]->n == 2*t-1) //child is gonna full
      {
        // if child is full ,then split it
        splitChild(i+1,C[i+1]);
        // After split, the middle key of C[i] goes up and
        // C[i] is splitted into two. See which of the two
        // is going to have the new key
        if(keys[i+1]<k)
        {
          i++;
        }
      }
      C[i+1]->insertNonFull(k);
    }
  }
  // split the child y of this node,i is index of y in child array
  // C[],The Child y must be full when the function is called
  void splitChild(BTreeNode *y,int i)
  {
    BTreeNode *z = new BTreeNode(y->t,y->leaf);
    z->n = t-1;
    for(int j=0;j<t-1;j++)
    {
      z->keys[j] = y->keys[j+t];
    }
    if(y->leaf==false)
    {
      for(int j=0;j<t;j++)
      {
        z->C[j] = y->C[j+t];
      }
    }
    y-> = t - 1;
    // create new child
    for(int j=n;j>=i+1;j--)
    {
      C[j+1] = C[j];
    }
    C[i+1] = z;
    for(int j=n-1;j>=i;j--)
    {
      keys[j+1] = keys[j];
    }
    keys[i] = y->keys[t-1];

    n++;
  }
  friend class BTree;
};
class BTree
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
    if(!root) root->traverse();
  }
  BTreeNode* search(int k)
  {
    return root == NULL ? NULL : root->search(k);
  }
  void insert(int k)
  {
    if(root == NULL)
    {
      root = new BTreeNode(t,true);
      root->keys[0] = k;
      root->n = 1;
    }
    else
    {
      if(root->n == 2*t-1)
      {
        BTreeNode *s = new BTreeNode(t,false);
        s->C[0] = root;
        s->splitChild(0,root);
        int i=0;
        if(s->keys[i]<k)
        {
          i++;
        }
        s->C[i]->insertNonFull(k);
        root = s;
      }
      else
      {
        root->insertNonFull(k);
      }
    }
  }
}
