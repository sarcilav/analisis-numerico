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

int main (){
  int rows;
  scanf("%d",&rows);
  double A[rows][rows];
  for(int i=0;i<rows;++i)
    for(int j=0;j<rows;++j)
      scanf("%lf",&A[i][j]);
  
  double L[rows][rows];
  double U[rows][rows];
  memset(L,0,sizeof(L));
  memset(U,0,sizeof(U));

  double acum;
  for(int k=0;k<rows;++k){
    acum=A[k][k];
    for(int p=0;p<k-1;++p){
      acum-=L[k][p]*U[p][k];
    }//p
    U[k][k]=L[k][k]=sqrt(acum);
    
    for(int i=k;i<rows;++i){
      acum=A[i][k];
      for(int r=0;r<k-1 ;++r){
	acum-=L[i][r]*U[r][k];
      }//r
      L[i][k]=acum/L[k][k];
    }//i
    for(int j=k;j<rows;++j){
      acum=A[k][j];
      for(int s=0;s<k-1;++s){
	acum-=L[k][s]*U[s][j];
      }//s
      U[k][j]=acum/L[k][k];
    }//j
  }//k

  
  puts("L");
  D_m(L,rows,rows);
  puts("U");
  D_m(U,rows,rows);
  puts("A");
  D_m(A,rows,rows);
  
  return 0;
}
