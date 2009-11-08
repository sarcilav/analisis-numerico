/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "punto_fijo.h"
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
void secante(double x0, double x1, double tol, int it)
{
  double y0 = f(x0);

  if(y0 == 0)
    printf("%lf es raíz\n", x0);
  else
    {
      double y1 = f(x1);
      double E = tol+1;
      double xa;
      int cont = 0;
      printf("%d %lf %lf %lf %lf\n",cont,x0,x1,y1,E);
      while(y1!=0 && E>=tol && y1!=y0 && cont<it)
	{
	  xa = x1;
	  x1 = x1 - y1*(x1-x0)/(y1-y0);
	  x0 = xa;
	  y0 = y1;
	  y1 = f(x1);
	  E = fabs(x1-x0);
	  ++cont;
	  printf("%d %.10lf %.10lf %e %e\n",cont,x0,x1,y1,E);
	}
      if(y1==0)
	printf("%lf es raíz\n",x1);
      else
	if(E<tol)
	  printf("%.100lf es raíz con error\n",x1);
	else
	  puts("No hay raíz");
    }
}

int main()
{
  secante(10.4,10.470861,1e-8,100);
  return 0;
}
