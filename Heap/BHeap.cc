#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <limits>
using namespace std;
struct  Node
{
  Node(int data)
      :k(0),data(data)
  {}
  int k;
  int data;
  vector<Node*> child;
};
Node *merge(Node *p,Node *q)
{
  assert((p==NULL) || (q==NULL) || (p->k == q->k));
  if(p == NULL) return q;
  if(q == NULL) return p;
  if(q->data < p->data)
  {
    swap(p,q);
  }
  p->child.push_back(q);
  p->k++;
  return p;
}
class Heap
{
 public:
  Heap()
  {}
  void insert(int data)
  {
    Node * node = new Node(data);
    Heap h;
    h.addChild(node,0);
    merge(h);
  }
  bool isEmpty()
  {
    for(auto r : child)
    {
      if(r!=NULL) return false;
    }
    return true;
  }
  int getMin()
  {
    assert(!isEmpty());
    int minv = numeric_limits<int>::max();
    for(auto r : child)
    {
      if(r!=NULL)
      {
        minv = min(minv,r->data);
      }
    }
    return minv;
  }
  void extractMin()
  {
    assert(!isEmpty());
    Node *minr = NULL;
    int minv = numeric_limits<int>::max();
    for(auto r : child)
    {
      if(r!=NULL && r->data < minv)
      {
        minr = r;
        minv = r->data;
      }
    }
    addChild(NULL,minr->k);
    Heap h;
    for(auto ch : minr->child)
    {
      h.addChild(ch,ch->k);
    }
    merge(h);
  }
  void addChild(Node *ch,int k)
  {
    if(k>=child.size())
    {
      child.resize(k+1);
    }
    child[k]=ch;
  }
  void merge(Heap &h)
  {
    Node *p,*q,*carry;
    int m =child.size();
    int n = h.child.size();
    int i=0,j=0;
    carry = NULL;
    while(i<m || j<n || carry)
    {
      p = i<m ? child[i] : NULL;
      q = j<n ? h.child[j] : NULL;
      Node * t[3]={NULL,NULL,NULL};
      int k=0;
      if(p!=NULL) t[k++]=p;
      if(q!=NULL) t[k++]=q;
      if(carry!=NULL) t[k++]=carry;
      if(k==3)
      {
        addChild(t[0],i);
        carry = ::merge(t[1],t[2]);
      }
      else if(k==2)
      {
        addChild(NULL,i);
        carry = ::merge(t[0],t[1]);
      }
      else if(k==1)
      {
        addChild(t[0],i);
        carry = NULL;
      }
      else
      {
      }
      i++;
      j++;
    }
  }
 private:
  vector<Node*> child;
};
int main()
{
  int n = 50;
  int arr[n];
  for(int i=0;i<n;i++)
  {
    arr[i]=rand()%100;
  }
  Heap h;
  for(int i=0;i<n;i++)
  {
    h.insert(arr[i]);
  }
  while(!h.isEmpty())
  {
    int x = h.getMin();
    h.extractMin();
    cout<<x<<endl;
  }
}
