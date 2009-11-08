/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
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
void sustitucion_regresiva(int n)
{
  int I = n;
  double x[n];

  while(I--)
    {

      double acum = 0;
      for(int i = I+1; i<n ; ++i)
	acum += x[i]*a[I][i];
      x[I] = (a[I][n] - acum)/a[I][I];
      
    }
  puts("---ANS---");
  for(int i = 0; i < n; ++i)
    printf("X_%d=%lf ",i+1,x[i]);
  puts("");
}
pair<double, pair<int,int> > mayor(int etapa,int n)
{
  double _m_ = 0;
  int fila = -1;
  int col = -1;
  for(int i = etapa; i<n; ++i)
    {
      for(int j = etapa ; j<n; ++j)
	if(_m_ < fabs(a[i][j]))
	  {
	    _m_ = a[i][j];
	    fila = i;
	    col = j;
	  }
    }
  pair<int,int> coord (fila,col);
  return pair<double, pair<int,int> > (_m_,coord);
}
#define SWAP_FILA(__I ,__J) for(int __i = 0; __i<=n;++__i) swap(a[__I][__i],a[__J][__i]);
#define SWAP_COL(__I,__J) for(int __j = 0; __j<=n;++__j) swap(a[__j][__I], a[__j][__J]);
void eliminacion_total(int n)
/*a[n][n+1] es la matriz expandida n es el numero de x*/
{

  for(int k = 0; k<n-1; ++k)
    {
      pair<double, pair<int,int> > MAX = mayor(k,n);
      if(MAX.first == 0)
	{
	  puts("We have problems!!!");
	  exit(0);	    
	}
      pair<int,int> & coord = MAX.second;
      if(coord.first != k)
	SWAP_FILA( k , coord.first);
      if(coord.second != k)
	SWAP_COL(k,coord.second);
      for(int i = k+1; i<n ; ++i)
	{
	  double mik = a[i][k] / a[k][k] ;
	  printf("m[%d][%d] = %lf ",i,k,mik);

	  for(int j = k ; j<=n;++j)
	    a[i][j] = a[i][j] - mik*a[k][j];
	}
      puts("");
      //DEBUG DE CADA ITERACION
      printf("Etapa %d\n",k+1);
      for(int i = 0; i<n ; ++i)
	{
	  for(int j = 0; j<=n ; ++j)
	    printf("%lf ",a[i][j]);
	  puts("");
	}
    }
  sustitucion_regresiva(n);
}
int main()
{
  int n;
  puts("Ingrese tamaño matriz");
  scanf("%d",&n);
  
  double _tt;
  for(int i = 0; i<n ; ++i)
    for(int j = 0; j<=n && scanf("%lf",&_tt) == 1;++j)
      a[i][j] = _tt;
  
  eliminacion_total(n);
  
  return 0;
}
