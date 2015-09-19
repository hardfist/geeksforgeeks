#include <string>
#include <iostream>
using namespace std;
void miniString(string s)
{
  int n = s.size();
  int lo =0,hi=n-1;
  while(lo<=hi)
  {
    bool left = false;
    for(int i=0;lo+i<=hi;i++)
    {
      if(s[lo+i] < s[hi-i])
      {
        left = true;
        break;
      }
      else if(s[lo+i] > s[hi-i])
      {
        left = false;
        break;
      }
    }
    if(left)
    {
      putchar(s[lo++]);
    }
    else
    {
      putchar(s[hi--]);
    }
  }
}
int main()
{
  miniString("acdbcb");
  cout<<endl;
}
