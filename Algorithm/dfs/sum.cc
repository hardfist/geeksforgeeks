#include <iostream>
using namespace std;
const int max_n = 100;
int solution[max_n];
int i=0;
void printSolution()
{
  for(int k=0;k<i;k++)
  {
    cout<<solution[k]<<" ";
  }
  cout<<endl;
}
bool dfs(int a[],int n,int k,int sum)
{
  if(sum == 0)
  {
    return true;
  }
  if(k>=n)
  {
    return false;
  }
  if(dfs(a,n,k+1,sum)) return true;
  solution[i++]=a[k];
  if(dfs(a,n,k+1,sum-a[k])) return true;
  i--;
  return false;
}
int main()
{
  int n = 4;
  int a[]={1,2,4,7};
  int k = 13;
  cout<<dfs(a,n,0,k)<<endl;
  printSolution();
}
