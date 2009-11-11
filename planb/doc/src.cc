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
  float a,b,c ,d;
  Cubic ( ) { }
  Cubic(float A, float B, float C, float D){
    a = A;
    b = B;
    c = C;
    d = D;
  }


  /** evaluate cubic */
  float eval(float u) {
    return (((d*u) + c)*u + b)*u + a;
  }

};


struct polygon
{
  vector <float > X;
  vector <float > Y;
  polygon ( ) { }
  void addPoint ( float xx, float yy)
  {
    X.push_back ( xx ) ;
    Y.push_back ( yy ) ;
  }
};

vector<Cubic> calcular_cubicas(const int & n, const vector<float> & xx) {
  float w [n+1], v[n+1], yy[n+1], D [n+1];
  float z, F, G, H;
  int k;
  w[1] = v[1] = z = 1.0f/4.0f;
  yy[0] = z * 3 * (xx[1] - xx[n]);
  H = 4;
  F = 3 * (xx[0] - xx[n-1]);
  G = 1;
  for ( k = 1; k < n; k++) {
    v[k+1] = z = 1/(4 - v[k]);
    w[k+1] = -z * w[k];
    yy[k] = z * (3*(xx[k+1]-xx[k-1]) - yy[k-1]);
    H = H - G * w[k];
    F = F - G * yy[k-1];
    G = -v[k] * G;
  }
  H = H - (G+1)*(v[n]+w[n]);
  yy[n] = F - (G+1)*yy[n-1];

  D[n] = yy[n]/H;
  D[n-1] = yy[n-1] - (v[n]+w[n])*D[n];
  for ( k = n-2; k >= 0; k--) {
    D[k] = yy[k] - v[k+1]*D[k+1] - w[k+1]*D[n];
  }


  /* now compute the coefficients of the cubics */
  vector<Cubic> C (n+1);
  for ( k = 0; k < n; k++) {
    C[k] =  Cubic(xx[k], D[k], 3*(xx[k+1] - xx[k]) - 2*D[k] - D[k+1],
                     2*(xx[k] - xx[k+1]) + D[k] + D[k+1]);
  }

  C[n] = Cubic(xx[n], D[n], 3*(xx[0] - xx[n]) - 2*D[n] - D[0],
               2*(xx[n] - xx[0]) + D[n] + D[0]);
  return C;
}


polygon doit(){
  int STEPS = 12;
  polygon p ;
  if (x.size() > 2) {
    vector<Cubic> X = calcular_cubicas(x.size()-1, x);
    vector<Cubic> Y = calcular_cubicas(y.size()-1, y);
    p.addPoint(X[0].eval(0),Y[0].eval(0));
    for (int i = 0; i < X.size(); i++) {
      for (int j = 1; j <= STEPS; j++) {
        float u = j / (float) STEPS;
        p.addPoint(X[i].eval(u),Y[i].eval(u));
      }
    }
  }
  return p;
}

