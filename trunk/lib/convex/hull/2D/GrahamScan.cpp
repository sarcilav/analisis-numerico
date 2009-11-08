/* 
   TODO hacer los .h
 */
#include<algorithm>
#include <vector>
#include <math.h>
using namespace std;
//Graham scan: Complexity: O(n log n)
struct point
{
  int x,y;
  point() {}
  point(int X, int Y) : x(X), y(Y) {}
};
point pivot;

inline int distsqr(const point &a, const point &b)
{
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
inline double dist(const point &a, const point &b)
{
  return sqrt(distsqr(a, b));
}

//retorna > 0 si c esta a la izquierda del segmento AB
//retorna < 0 si c esta a la derecha del segmento AB
//retorna == 0 si c es colineal con el segmento AB
inline int cross(const point &a, const point &b, const point &c)
{
  return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}
//Self < that si esta a la derecha del segmento Pivot-That
bool angleCmp(const point &self, const point &that)
{
  int t = cross(pivot, that, self);
  if (t < 0) return true;
  if (t == 0)
    {
      //Self < that si est ́ m ́s cerquita
      return (distsqr(pivot, self) < distsqr(pivot, that));
    }
  return false;
}


vector<point> graham(vector<point> p)
{
//Metemos el m ́s abajo m ́s a la izquierda en la posici ́n 0
  
  for (int i=1; i<p.size(); ++i)
    {
      if (p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x))
	swap(p[0], p[i]);
     
    }
  pivot = p[0];
  sort(p.begin(), p.end(), angleCmp);
  //Ordenar por  ́ngulo y eliminar repetidos.
  
  //Si varios puntos tienen el mismo angulo el m ́s lejano
  
  //queda despu ́s en la lista
  
  vector<point> chull(p.begin(), p.begin()+3);
  
  for(int i = 3; i< p.size();++i)
    {
      while (chull.size() >= 2 
	     && cross(chull[chull.size()-2],chull[chull.size()-1],p[i]) <=0)
	{
	  chull.erase(chull.end() - 1);
	}
      chull.push_back(p[i]);
    }
  //chull contiene los puntos del convex hull ordenados
  //anti-clockwise. No contiene ning ́n punto repetido. El

  //primer punto no es el mismo que el  ́ltimo, i.e, la  ́ltima
  
  //arista va de chull[chull.size()-1] a chull[0]
  return chull;
}

