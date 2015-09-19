#include <iostream>
using namespace std;
void permutation(int a[],int n,int k,bool marked[],int perm[])
{
  if(k==n)
  {
    for(int i=0;i<n;i++)
    {
      cout<<a[perm[i]]<<" ";
    }
    cout<<endl;
  }
  for(int i=0;i<n;i++)
  {
    if(!marked[i])
    {
      marked[i] = true;
      perm[k]=i;
      permutation(a,n,k+1,marked,perm);
      marked[i] = false;
    }
  }
}
int main()
{
  int a[]={1,2,3,4};
  const int n = sizeof(a)/sizeof(a[0]);
  bool marked[n];
  int perm[n];
  for(int i=0;i<n;i++)
  {
    marked[i] =false;
  }
  permutation(a,n,0,marked,perm);
}
