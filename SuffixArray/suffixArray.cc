#include <iostream>
#include <vector>
using namespace std;
vector<int> build_sa(const char *txt)
{
  int n = strlen(txt);
  vector<int> sa(n+1);
  vector<int> rank(n+1);
  int tmp[n+1];
  for(int i=0;i<=n;i++)
  {
    sa[i] = i;
    rank[i] = txt[i];
  }
  int k=0;
  auto cmp = [&k,&rank,&n](int i,int j)
  {
    if(rank[i]!=rank[j]) return rank[i] < rank[j];
    else
    {
      int ri = i+k <= n ? rank[i+k] : -1;
      int rj = j+k <=n ? rank[j+k] : -1;
      return ri < rj;
    }
  };
  for(k=1;k<=n;k*=2)
  {
    sort(sa.begin(),sa.end(),cmp);
    tmp[sa[0]] = 0;
    for(int i=1;i<=n;i++)
    {
      tmp[sa[i]] = tmp[sa[i-1]] +( cmp(sa[i-1],sa[i]) ? 1 : 0);
    }
    for(int i=0;i<=n;i++)
    {
      rank[i] = tmp[i];
    }
  }
  return sa;
}
// int lower_bound(const char *txt,const char *pat)
// {
//   vector<int> res = build_sa(txt);
  
// }
bool contain(const char *txt,const char *pat)
{
  vector<int> sa = build_sa(txt);
  for(int i=0;i<sa.size();i++)
  {
    cout<<txt+sa[i]<<endl;
  }
  int lo=0,hi=strlen(txt)+1;
  int m = strlen(pat);
  // (lo,hi) ?  a[0,lo]<k a[hi,n+1)>=k
  while(hi-lo>1)
  {
    int mid = (lo+hi)/2;
    int cmp =strncmp(pat,txt+sa[mid],m);
    if(cmp<0) //a[mid] < k
    {
      lo = mid; // (mid,hi) ?
    }
    else
    {
      // a[mid]>=k
      hi=mid; // a(lo,hi) ?
    }
  }
  // hi = lo+1 => a[0,lo]<k a[hi,n+1) >=k
  return strncmp(pat,txt+sa[hi],m) == 0;
}
vector<int> build_lcp(const char *txt)
{
  vector<int> sa = build_sa(txt);
  int n = strlen(txt);
  vector<int> lcp(n+1);
  int rank[n+1];
  for(int i=0;i<=n;i++) rank[sa[i]]= i;
  int h= 0;
  lcp[0] = 0;
  for(int i=0;i<n;i++)
  {
    int j = sa[rank[i]-1];
    if(h>0) h--;
    for(;j+h<n && i+h < n;h++)
    {
      if(txt[j+h]!=txt[i+h]) break;
    }
    lcp[rank[i]-1]=h;
  }
  return lcp;
}
void longestCommonSubstring(const char *s,const char *t)
{
  int n = strlen(s);
  int m = strlen(t);
  char str[n+m+1+1];
  str[0]='\0';
  strcat(str,s);
  strcat(str,"$");
  strcat(str,t);
  puts(str);
  vector<int> sa = build_sa(str);
  vector<int> lcp = build_lcp(str);
  int len = n+m+1;
  int ans = 0;
  for(int i=0;i<len;i++)
  {
    if((sa[i]<n)!=(sa[i+1]<n))
    {
      ans = max(ans,lcp[i]);
    }
  }
  printf("%d\n",ans);
}
#if 0
int main()
{
  const char *txt = "abracadabra";
  vector<int> res = build_sa(txt);
  vector<int> lcp = build_lcp(txt);
  for(int x : res)
  {
    cout<<x<<" ";
  }
  cout<<endl;
  for(int x : lcp)
  {
    cout<<x<<" ";
  }
  cout<<endl;
}
#endif
#if 1
int main()
{
  const char *s="abracadabra";
  const char *t="ecadadabrbcrdar";
  longestCommonSubstring(s,t);
}
#endif
