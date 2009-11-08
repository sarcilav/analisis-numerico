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
  double x=2.5;
  while(scanf("%lf",&x)==1){  
    puts("------------------------------------");
    double nv[n+1][n+1];
    memset(nv,0,sizeof(nv));
    for(int i=0;i<n; nv[0][i]=F[i++]); //F() to use the method for the function

    for(int i=1;i<n;++i)
      for(int j=i;j<n;++j)//truncamiento porque viene de lagrage y redondeo porque mas digitos
	nv[i][j]=(((x-X[j-i])*nv[i-1][j])-((x-X[j])*nv[i-1][j-1]))/(X[j]-X[j-i]);
  
    for(int i=0;i<n;++i,puts(""))
      for(int j=0;j<n; printf("%10lg ",nv[i][j++]));
    printf("interpolación de %lg = %lf\n",x,nv[n-1][n-1]);  
    puts("------------------------------------");
  }
  return 0;
}
