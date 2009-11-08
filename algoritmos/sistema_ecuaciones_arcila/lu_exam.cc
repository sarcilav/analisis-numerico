/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "cholesky.h"
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
double a[MAXN][MAXN], l[MAXN][MAXN], u[MAXN][MAXN], b[MAXN], z[MAXN];

void cholesky(int n)
{
  l[0][0] = 3;
  l[1][1] = 3;
  l[2][2] = 2;
  for(int k = 0; k<n; ++k)
    {
      double sum = 0;
      for(int p = 0; p<k; ++p)
	sum += (l[k][p]*u[p][k]);
      u[k][k] = (a[k][k] - sum)/l[k][k];
      
      for(int i = k; i<n; ++i)
	{
	  sum = 0;
	  for(int r = 0; r<k; ++r)
	    sum += (l[i][r]*u[r][k]);
	  l[i][k] = (a[i][k] - sum) / u[k][k];
	}
      
      for(int j = k; j<n; ++j)
	{
	  sum = 0;
	  for(int s = 0; s<k; ++s)
	    sum += (l[k][s]*u[s][j]);
	  u[k][j] = (a[k][j] - sum)/l[k][k];
	}

      //DEBUG
      printf("Etapa %d\n",k+1);
      puts("L");
      for(int i = 0; i<n; ++i,puts(""))
	for(int j = 0; j<n; ++j)
	  printf("%lf ",l[i][j]);
      puts("U");
      for(int i = 0; i<n; ++i,puts(""))
	for(int j = 0; j<n; ++j)
	  printf("%lf ",u[i][j]);
    }
}

void sustitucion_regresiva(int n)
{
  int I = n;
  double x[n];
  while(I--)
    {

      double acum = 0;
      for(int i = I+1; i<n ; ++i)
	acum += x[i]*u[I][i];
      x[I] = (z[I] - acum)/u[I][I];
      
    }
  puts("---ANS---");
  for(int i = 0; i < n; ++i)
    printf("x_%d=%lf ",i+1,x[i]);
  puts("");
}

void sustitucion_progresiva(int n)
{
  for(int I = 0; I<n; ++I)
    {
      double acum = 0;
      for(int i=0; i <I ; ++i)
	acum += z[i]*l[I][i];
      z[I] = (b[I] -acum)/l[I][I];
      
    }
  puts("---Z---");
  for(int i = 0; i < n; ++i)
    printf("z_%d=%lf ",i+1,z[i]);
  puts("");
}

int main()
{
  puts("Ingrese el tamaño de la matriz");
  int n;
  scanf("%d",&n);

  memset(l, 0 , sizeof l);
  memset(u, 0 , sizeof u);
  puts("Ingrese la matriz A sin b");
  double _tt;
  for(int i = 0; i<n; ++i)
    for(int j = 0; j<n && scanf("%lf",&_tt) == 1; ++j)
      a[i][j] = _tt;
      
  cholesky(n);
  puts("Ingrese b");
  for(int i = 0; i<n && scanf("%lf",&_tt) == 1; ++i)
    b[i] = _tt;
  sustitucion_progresiva(n);
  sustitucion_regresiva(n);
  
  return 0;
}
