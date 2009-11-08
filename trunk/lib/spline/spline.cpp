#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define STEP 4

using namespace std;

typedef double CoordType;

struct Point
{
  CoordType x,y;
  Point(){}
  Point(CoordType a, CoordType b): x(a), y(b){}
  bool operator < (const Point &p) const
  {
    return x<p.x || (x==p.x && y<p.y);
  }
  bool operator == (const Point &p) const
  {
    return x==p.x && y==p.y;
  }
};

vector<Point> pedir_puntos()
{
  vector<Point> puntosEntrada;
  int n = 0;
  printf("ingrese el numero de puntos que desea interpolar:\n");
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    CoordType p, q;
    scanf("%lf %lf", &p, &q);
    Point s(p, q);
    puntosEntrada.push_back(s);
    printf("leido (%lf, %lf) \n", s.x, s.y);
  }
  return puntosEntrada;
}


int main(){

  vector<Point> entrada = pedir_puntos();
  int n = entrada.size();
  vector<double> h, b, u, v;
  double *z;
  double *A, *B, *C, *D; //coeficientes de la función de spline resultante
  z = new double[n+1]; //arreglo de resultados de la segunda derivada
  A = new double[n];
  B = new double[n];
  C = new double[n];
  D = new double[n];
  int i; //interador
  //creo la matriz tridiagonal que expresa la ecuación de la segunda derivada
  for(i = 0; i < n; ++i)
    {
    h.push_back(entrada[i+1].x-entrada[i].x);
    b.push_back(6*((entrada[i+1].y-entrada[i].y)/h[i]));
    }
  u.push_back(2*(h[0]+h[1]));
  v.push_back(b[1]-b[0]);
  //soluciono por gauss para vectores
  for(i = 1; i < n; ++i)
    {
      u.push_back( (2*(h[i] + h[i-1]) - (h[i-1]*h[i-1]))/u[i-1] );
      v.push_back((b[i]-b[i-1]-h[i-1]*v[i-1])/u[i-1]);       
    }
  // retorno el valor despejando gauss
  z[n]=0.0; //porque es una spline natural
  for(i = n-1; i >0; --i)
    z[i] = (v[i]-h[i]*z[i+1])/u[i];

  z[0] = 0.0; //porque es una spline natural

  //utilizo los resultados de la segunda derivada para conseguir los valores de los coeficientes
  for(i = 0; i < n; ++i)
    {
      A[i] = ((1/6)*h[i])* (z[i+1] - z[i]);
      B[i] = z[i] /2;
      C[i] = ((entrada[i+1].y - entrada[i].y)/h[i]) -(h[i]*z[i]/3) - (h[i]*z[i]/3) ;
    }

  //calculo ahora los valores de la spline
  //a partir del valor de los coeficientes con el método de horner
  //para estabilizar los cálculos
  for(i = 0; i < n; ++i)
    {
      double x = entrada[i].x;
      double sum = entrada[1].x/STEP;
      for(int j = 0; j < 4; ++j){
	double resultado = entrada[i].y + (x-entrada[i].x)*(C[i] + (x - entrada[i].x)*(B[i] + (x - entrada[i].x)*A[i]));
	printf("entrada: %lf\t salida: %lf\n", x, resultado);
	x+= sum;
      }

    }
  
  return 0;
}
