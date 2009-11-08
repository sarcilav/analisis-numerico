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
  double matrix[rows][rows+1];
  for(int i=0;i<rows;++i)
    for(int j=0;j<rows+1;++j)
      scanf("%lf",&matrix[i][j]);
  double acum;
  double X[rows];
  
  for(int i=0;i<rows;++i){
    acum=matrix[i][rows];
    for(int j=0;j<i;++j){
      acum-=matrix[i][j]*X[j];
    }
    X[i]=acum/matrix[i][i];
  }
  for(int i=0;i<rows;++i)
    printf("X%d->%lf\n",i+1,X[i]);
  return 0;
}
