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
  puts("*--Solución por Pivoteo Total--*");
  int rows;
  double aux=0;
  /*Read the matrix*/
  scanf("%d",&rows);  
  pair<double,int> matrix[rows][rows+1];
  for(int i=0;i<rows;++i)
    for(int j=0;j<rows+1;++j){
      scanf("%lf",&aux);
      matrix[i][j]=make_pair(aux,j);
    }

  /*Print the initial matrix*/
  puts("*--Initial Matrix--*");
  for(int __i=0;__i<rows;++__i){
    for(int __j=0;__j<=rows;++__j){
      printf("%lf ",matrix[__i][__j].first);
    }
    puts("");
  }
  
  /*Start the elimination method*/
  for(int i=0;i<rows-1;++i){

    //Find the biggest in column and row
    double max=abs(matrix[i][i].first);
    int indexi=i,indexj=i;
    for(int _i_=i;_i_<rows;++_i_){
      for(int _j_=i;_j_<rows;++_j_){
	if(abs(matrix[_i_][_j_].first)>max){
	  max=abs(matrix[_i_][_j_].first);
	  indexi=_i_;
	  indexj=_j_;
	}
      }
    }
    //Swap rows and columns
    if(indexi!=i){
      aux=0;
      for(int k=0;k<=rows;++k){//<=rows == cols
	aux=matrix[i][k].first;
	matrix[i][k].first=matrix[indexi][k].first;
	matrix[indexi][k].first=aux;
      }
    }
    if(indexj!=i){
      pair<double,int> aux;
      for(int k=0;k<rows;++k){
	aux=matrix[k][i];
	matrix[k][i]=matrix[k][indexj];
	matrix[k][indexj]=aux;
      }
    }
    
    
    //Column with zeros
    double m;    
    for(int j=i+1;j<rows;++j){
      m=( matrix[j][i].first/matrix[i][i].first);
      for(int k=i;k<rows+1;++k){
	matrix[j][k].first = (matrix[j][k].first-m*matrix[i][k].first);
      }
    }
  }

  /*Print the zeroed matrix*/
  puts("\n*--Superior triangular matrix--*");
  for(int __i=0;__i<rows;++__i){
    for(int __j=0;__j<=rows;++__j){
      printf("%lf ",matrix[__i][__j].first);
    }
    puts("");
  }
  
  /*Substitution*/
  double acum;
  double X[rows];
  for(int i=rows-1;i>=0;--i){
    acum=matrix[i][rows].first;
    printf("");
    for(int j=rows-1;j>i;--j){
      acum-=matrix[i][j].first*X[matrix[i][j].second];
    }
    X[matrix[i][i].second]=acum/matrix[i][i].first;
  }
  
  /*Print the solution*/
  puts("\n*--Solution--*");
  for(int i=0;i<rows;++i)
    printf("X%d->%lf\n",i+1,X[i]);
  
  return 0;
}
