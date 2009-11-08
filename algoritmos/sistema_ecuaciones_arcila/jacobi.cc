/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "jacobi.h"
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>

using namespace std;

/* DEBUG */
#define D(x) cerr<<__LINE__<<" "#x" "<<x<<endl
#define D_v(x) for(int i=0;i<x.size();cerr<<x[i++]<<" ")

#define ALL(x) x.begin(),x.end()
#define MAXN 101
double a[MAXN][MAXN];
double g(double x[MAXN],int n,int I)
{
  double acum=0;
  for(int i = 0; i<n;++i)
    if(i!=I)
      acum += (x[i]*a[I][i]);
  return (a[I][n] - acum)/a[I][I];
}
void jacobi(double x[MAXN],double tol,int it ,int  n)
{
  double E = tol + 1;
  int cont = 0;
  double xn[MAXN];
  memcpy(xn,x, MAXN*sizeof(double));
  //for(int i = 0; i< MAXN; ++i)
  //   assert(x[i] == xn[i]);
  while(E>= tol && cont <it)
    {
      E = 0;
      for(int i = 0; i<n; ++i)
	{
	  x[i] = g(xn,n,i);
	  E = max(E,fabs(x[i]-xn[i]));
	  //E /= x[i];
	}
      memcpy(xn,x, MAXN*sizeof(double));
      ++cont;      
      //DEBUG
      printf("Iteración %d\n",cont);
      for(int i = 0; i<n; ++i)
	printf("X_%d = %lf ",i+1,x[i]);
      printf(" Error =%e\n",E);
    }
  if(E>= tol) puts("No encontre respuesta");
}


int main()
{
  puts("Ingrese el tamaño de la matriz");
  int n;
  scanf("%d",&n);
  
  puts("Ingrese la matriz");
  double _tt;
  for(int i = 0; i<n; ++i)
    for(int j = 0; j<=n && scanf("%lf",&_tt) == 1; ++j)
      a[i][j] = _tt;
  
  double x[MAXN];
  puts("Ingrese los valores iniciales");
  for(int i = 0; i<n && scanf("%lf",&x[i]) == 1; ++i);
  
  puts("Ingrese la tolerancia y el numero de iteraciones");
  double tol;
  int it;
  scanf("%lf %d",&tol,&it);
  
  jacobi(x,tol,it,n);
  
  return 0;
}
