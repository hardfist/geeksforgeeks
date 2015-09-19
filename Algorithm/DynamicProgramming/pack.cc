#include <iostream>
using namespace std;
int dfs(int k,int sum,int n,int weight[],int value[])
{
  if(k>=n) return 0;
  if(sum<=0) return 0;
  int res = 0;
  if(weight[k]<=sum)
  {
    res = dfs(k+1,sum-weight[k],n,weight,value)+value[k];
  }
  res = max(res,dfs(k+1,sum,n,weight,value));
  return res;
}
int rec(int sum,int n,int weight[],int value[])
{
  int dp[n+1][sum+1];
  memset(dp,0,sizeof(dp));
  for(int i=n-1;i>=0;i--)
  {
    for(int j=0;j<=sum;j++)
    {
      if(j<weight[i])
      {
        dp[i][j] = dp[i+1][j];
      }else
      {
        dp[i][j] = max(dp[i+1][j],dp[i+1][j-weight[i]]+value[i]);
      }
    }
  }
  return dp[0][sum];
}
int main()
{
  int weight[] ={2,1,3,2};
  int value[] ={3,2,4,2};
  cout<<dfs(0,5,4,weight,value)<<endl;
  cout<<rec(5,4,weight,value)<<endl;
}
