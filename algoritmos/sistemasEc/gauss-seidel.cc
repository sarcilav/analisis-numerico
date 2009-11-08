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

/*Valores Iniciales*/
  double X[]={0,0,0};

/* Ecuaciones */
/*
  8x1  + 2x2  + 15x3 = 50
  20x1 + 8x2  + 5x3  = 250
  5x1  + 50x2 + 6x3  = -100

estrictamente diagonalmente dominante
  20x1 +8x2  + 5x3  = 250
  5x1  +50x2 + 6x3  = -100
  8x1  +2x2  + 15x3 = 50
 */
double EC(int i){
  if(i==0)
    return ( 250 -8*X[1] -5*X[2]) / 20.0;
  else if(i==1)
    return (-100 -5*X[0] -6*X[2]) / 50.0;
  else
    return (50 -8*X[0] -2*X[1]) / 15.0 ;
}

void gauss_seidel(double tol, int it){
  int count =0;
  double E=tol+1;
  int size=sizeof(X)/sizeof(X[0]);
  for(int i=0;i<size;printf("%10d",i++));puts("");
  printf("%3d | ",0);
  for(int i=0;i<size;printf("%.6lf  ",X[i++]));puts("");


  while( E>tol && count<it ){
    E=0;
    double aux;
    for( int i=0 ; i<size ; ++i ){
      aux=X[i];
      X[i]=EC(i);
      E=max(E,abs(X[i]-aux));
    }
    count+=1;
    printf("%3d | ",count);
    for(int i=0;i<size;printf("%.6lf  ",X[i++]));
    printf("%lg\n",E);
  }
  //  for(int i=0;i<size;printf("X%d ->  %lf\n",i,X[i++]));
}

int main (){
  double tol=1e-5;
  int it=20;
  gauss_seidel(tol,it);
  return 0;
}
