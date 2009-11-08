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
  puts("*--Solución por Pivoteo Parcial--*");
  int rows;
  scanf("%d",&rows);
  double matrix[rows][rows+1];
  for(int i=0;i<rows;++i)
    for(int j=0;j<rows+1;++j)
      scanf("%lf",&matrix[i][j]);
  puts("*--Initial Matrix--*");
  D_m(matrix,rows,rows+1);
  for(int i=0;i<rows-1;++i){
    //Find the biggest in column
    double max=abs(matrix[i][i]);
    int index=i;
    for(int j=i;j<rows;++j){
      if(abs(matrix[j][i])>max){
	max=abs(matrix[j][i]);
	index=j;
      }
    }
    //Swap rows
    if(index!=i){
      double aux=0;
      for(int k=0;k<=rows;++k){//<=rows == cols
	aux=matrix[i][k];
	matrix[i][k]=matrix[index][k];
	matrix[index][k]=aux;
      }
    }
    //Column with zeros
    double m;    
    for(int j=i+1;j<rows;++j){
      m=( matrix[j][i]/matrix[i][i]);
      for(int k=i;k<rows+1;++k){
	matrix[j][k] = (matrix[j][k]-m*matrix[i][k]);
      }
    }
  }
  puts("*--Superior triangular matrix--*");
  D_m(matrix,rows,rows+1);
  
  //Substitution
  double acum;
  double X[rows];
  for(int i=rows-1;i>=0;--i){
    acum=matrix[i][rows];
    printf("");
    for(int j=rows-1;j>i;--j){
      acum-=matrix[i][j]*X[j];
    }
    X[i]=acum/matrix[i][i];
  }
  puts("*--Solution--*");
  for(int i=0;i<rows;++i)
    printf("X%d->%lf\n",i+1,X[i]);
  
  return 0;
}
