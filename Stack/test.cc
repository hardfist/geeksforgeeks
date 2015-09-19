#include <iostream>
#include <vector>
using namespace std;
int main()
{
  vector<int> v={1};
  v[1] =2;
  v[3]= 3;
  v[10000]=100;
  for(int i=0;i<10000;i++)
  {
    cout<<v[i]<<endl;
  }
}
