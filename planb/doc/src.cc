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


struct Cubic
{

  float a,b,c,d;         /* d + c*x + b*x^2 +a*x^3 */
  Cubic(){}
  Cubic(float d, float c, float b, float a)
  {
    this.a = a;
    this.b = b;
    this.c = c;
    this.d = d;
  }


  /** evaluate cubic */
  float eval(float u)
  {
    return (((a*u) + b)*u + c)*u + d;
  }
};
vector<Cubic> calcular_cubicas(const int &n, const vector<float> &x)
{
  float gamma [n+1],delta [n+1], D [n+1];

  int i;
  gamma[0] = 1.0f/2.0f;
  for ( i = 1; i < n; ++i)
    gamma[i] = 1/(4-gamma[i-1]);
  gamma[n] = 1/(2-gamma[n-1]);
  delta[0] = 3*(x[1]-x[0])*gamma[0];
  for ( i = 1; i < n; ++i)
    delta[i] = (3*(x[i+1]-x[i-1])-delta[i-1])*gamma[i];
  delta[n] = (3*(x[n]-x[n-1])-delta[n-1])*gamma[n];
  D[n] = delta[n];
  for ( i = n-1; i >= 0; --i)
    D[i] = delta[i] - gamma[i]*D[i+1];
  vector<Cubic> C(n);
  for ( i = 0; i < n; i++)
    C[i] =  Cubic((float)x[i], D[i], 3*(x[i+1] - x[i]) - 2*D[i] - D[i+1],
                  2*(x[i] - x[i+1]) + D[i] + D[i+1]);
  return C;
}
struct polygon
{
  int size;
  vector<float> X;
  vector<float> Y;
  polygon(){}
  void addPoint(float x,float y)
  {
    ++size;
    X.push_back(x);
    Y.push_back(y);
  }
};
polygon spline(const polygon & ini)
{
  int STEPS = 12;
  vector<Cubic> X = calcular_cubicas(ini.size, ini.X);
  vector<Cubic> Y = calcular_cubicas(ini.size, ini.Y);

  polygon p;
  p.addPoint(X[0].eval(0),Y[0].eval(0));
  for (int i = 0; i < X.size(); ++i)
    for (int j = 1; j <= STEPS; ++j)
      {
        float u = j / (float) STEPS;
        p.addPoint(X[i].eval(u), Y[i].eval(u));
      }
  return p;
}
