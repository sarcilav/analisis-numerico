/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "regla_falsa.h"
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

double f(double x)
{
  return x*sin(x) - exp(-x*x-3)-2*x+30;
}
void regla_falsa(double xa,double xb, double tol, int it)
{
  double ya = f(xa);
  double yb = f(xb);
  if(ya*yb>0)
    puts("Intervalo invalido");
  else
    if(ya==0)
      printf("%lf es raíz\n",xa);
    else
      if(yb == 0)
	printf("%lf es raíz\n",xb);
      else
	{
	  double xm = xa - ya*(xa-xb)/(ya-yb);
	  double ym = f(xm);
	  double E=tol+1;
	  int cont = 1;
	  printf("%d %lf %lf %lf %lf %lf\n",cont,xa,xb,xm,ym,0.);
	  while(ym!=0 && E>=tol && cont < it)
	    {
	      double xaux= xm;
	      if(ym*ya>0)
		{
		  xa=xm,ya=ym;
		}
	      else
		{
		  xb=xm,yb=ym;
		}
	      xm= xa - ya*(xa-xb)/(ya-yb);
	      ym=f(xm);
	      E=fabs(xaux-xm)/fabs(xm);
	      ++cont;
	      printf("%d %lf %lf %lf %lf %lf\n",cont,xa,xb,xm,ym,E);
	    }
	  if(ym == 0)
	    printf("%lf es raíz\n",xm);
	  else
	    if(E<tol)
	      printf("%lf es raíz con error\n",xm);
	    else
	      puts("No hay raíz");
	}
}

int main()
{
  regla_falsa(10.4,10.8  ,1e-2,1000);
  return 0;
}
