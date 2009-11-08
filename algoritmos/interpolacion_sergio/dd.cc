// Sergio Botero - sergiobuj@gmail.com
// Title:
// Submitted:
// OJ:

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
#define all(x) x.begin(),x.end()
#define D(x) cout <<__LINE__<<"  "<<#x<<"  is  "<< x << endl
#define D_v(x) for(int __i=0;__i<x.size();cerr<<x[__i++]<<" ")
#define D_m(m,rows,cols) for(int __i=0;__i<rows;cout<<endl,++__i) for(int __j=0;__j<cols;) cout <<m[__i][__j++]<<"  "
#define SWAP(a,b)({(a)^=(b);(b)^=(a);(a)^=(b);})						

/*
  double F(double x){
  return x; //function
  }
*/
int main (){
  
  //comment when reading from stinput
  int n=6;
  double X[]={2,2.2,2.4,2.6,2.8,3};
  double F[]={8.818277,8.688986,8.445859,8.086761,7.617084,7.049787};
  
  /*
    int n;
    scanf("%d",&n);
    double X[n];
    for(int i=0;i<n;++i)scanf("%lf",&X[i]);
  */
  
  double dd[n+1][n+1];
  memset(dd,0,sizeof(dd));
  for(int i=0;i<n; dd[0][i]=F[i++]); //F() to use the method for the function
  
  for(int i=1;i<n;++i)
    for(int j=i;j<n;++j)
      dd[i][j]=(dd[i-1][j]-dd[i-1][j-1])/(X[j]-X[j-i]);
  
  for(int i=0;i<n;++i,puts(""))
    for(int j=0;j<n; printf("%10lg ",dd[i][j++]));
  
  for(int i=0;i<n;printf("b%d=%10lf  ",i,dd[i][i++]));
  puts("");
  

  puts("-1 to quit");
  double value,ans,term;
  while(scanf("%lf",&value)==1 && value!=-1){
    ans=dd[0][0];
    term=1;
    for(int i=1;i<n;++i){
      term=term*(value-X[i-1]);
      ans+=dd[i][i]*term;
    }
    printf("%lg --> %lf\n",value,ans);
  }

  return 0;
}
