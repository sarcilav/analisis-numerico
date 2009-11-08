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

double tol = 1e-5;
int it = 20;

int main (){
  int rows;
  scanf("%d",&rows);
  double A[rows][rows+1];
  for(int i=0;i<rows;++i)
    for(int j=0;j<rows+1;++j)
      scanf("%lf",&A[i][j]);
  double X[rows];
  double X1[rows];
  memset(X,0.0,sizeof(X));
  memset(X1,0.0,sizeof(X1));
  for(int i=0;i<rows;printf("%10d",i++));puts("");
  printf("%3d | ",0);
  for(int i=0;i<rows;printf("%.6lf  ",X[i++]));puts("");
  //  puts("Matriz");
  //  D_m(A,rows,rows+1);
  
  double E=tol+1;
  int count=0;
  while (E>tol && count < it){
    E=0;
    for(int i=0;i<rows;++i){
      double s1=0.0;
      for(int j=0;j<i;++j)
	s1+=A[i][j]*X1[j];
      double s2=0.0;
      for(int j=i+1;j<rows;++j)
	s2+=A[i][j]*X1[j];    
      X[i]=(A[i][rows]-s1-s2)/A[i][i];
      E=max(E,abs(X[i]-X1[i]));
    }
    for(int i=0;i<rows;++i)X1[i]=X[i];
    printf("%3d | ",count+1);
    for(int i=0;i<rows;printf("%.6lf  ",X[i++]));
    printf("%lg\n",E);
    ++count;
  }
  return 0;
}

