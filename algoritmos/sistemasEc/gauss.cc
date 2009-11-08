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
const int rows=4;
const int rows+1=5;  
double matrix[rows][rows+1]={ 
  {14,-1,5,1,13},
  {-8,13,-12,-4,-32},
  {-3,2,-7,4,-12},
  {-7,9,1,5,31}
};*/

//float capa(float num){
// return (floor(num*100))/100;
//}

int main (){
  int rows;
  scanf("%d",&rows);
  double matrix[rows][rows+1];

  for(int i=0;i<rows;++i)
    for(int j=0;j<rows+1;++j)
      scanf("%lf",&matrix[i][j]);
  printf("%d\n",rows);
  double m;
  for(int i=0;i<rows-1;++i){
    for(int j=i+1;j<rows;++j){
      m=( matrix[j][i]/matrix[i][i]);
      for(int k=i;k<rows+1;++k){
	matrix[j][k] = (matrix[j][k]-m*matrix[i][k]);
      }
    }
  }
  D_m(matrix,rows,rows+1);
  return 0;
}
