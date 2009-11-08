/*
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
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
  //Queme aquí su función
  return x*x-0.5;
}

void busquedas_inc(double x0, double d, int it)
{
  double y0 = f(x0);
  if( y0 == 0)
    printf("%lf es raíz\n",x0);
  else
    {
      double x1 = x0+d;
      double y1 = f(x1);
      int cont  = 1;
      while(y0*y1>0 && cont <it)
        {
          x0 = x1, y0 = y1;
          x1 += d;
          y1 = f(x1);
          printf("[%lf , %lf]\n",x0,x1);
          ++cont;
        }
      if(y1 == 0)
        printf("%lf es raíz\n",x1);
      else
        if(y0*y1<0)
          printf("[%lf , %lf] es un intervalo\n",x0,x1);
        else
          puts("Excedio el numero de iteraciones");
    }
}

int main()
{
  busquedas_inc(-1,0.1,20);
  return 0;
}
