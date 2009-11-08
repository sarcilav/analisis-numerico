/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "bisecciom.h"
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
  //Queme aquí su F(x)
  return x*x-3;
}
      
void bisection(double xa,double xb, double tol, int it)
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
	  double xm = (xa+xb)/2;
	  double ym = f(xm);
	  double E=tol+1;
	  int cont = 1;
	  while(ym!=0 && E>=tol && cont < it)
	    {
	      if(ym*ya>0)
		xa=xm,ya=ym;
	      else
		xb=xm,yb=ym;
	      xm=(xa+xb)/2;
	      ym=f(xm);
	      E=fabs(xa-xm);
	      ++cont;
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
  bisection(0.,100.  ,1e-9,100);
  return 0;
}
