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
  

  double L[n];
  memset(L,1.0,sizeof(L));
  for(int i=0;i<n;L[i++]=1);  
  //  for(int i=0;i<n;printf("%lf  ",L[i++]));  
  
  double x=2.5;puts("");
  for(int i=0;i<n;++i)
    for(int j=0;j<n;++j){
      if(i!=j){
	L[i]*=((x-X[j])/(X[i]-X[j]));
      }
    }
  double p=0;
  for(int i=0;i<n;p+=L[i]*F[i++]);
  
  for(int i=0;i<n;printf("L[%d]=%lf  ",i,L[i++]));
  puts("");
  printf("P(%lg)=%lf\n",x,p);  
 return 0;
}
