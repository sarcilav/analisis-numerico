// Sergio Botero
// Title:integracion
// Submitted:
// J:pacho

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
#define all(x) x.begin(),x.end()
#define D(x) cout <<__LINE__<<"  "<<#x<<"  is  "<< x << endl
#define D_v(x) for(int __i=0;__i<x.size();cerr<<x[__i++]<<" ")
#define D_m(m,rows,cols) for(int __i=0;__i<rows;cout<<endl,++__i) for(int __j=0;__j<cols;) cout <<m[__i][__j++]<<"  "
#define SWAP(a,b)({(a)^=(b);(b)^=(a);(a)^=(b);})						


double fun(double x){
  return ((exp(x))*(cos(x)))/(7*x); //function
}

/*
  Hay que tener mucho cuidado cuando se cambian el número de puntos, ya que
  pueden cambiar los intervalos en todas las funciones al calcular el h

  se puede cambiar entre ``quemar'' los valores en F[] o escribir la funcion.
  personalmente creo que la voy a sacar en excel y la quemo en F[]...(sospecho
  que en mi primer parcial me fue tan bien gracias a una funcion mal quemada)
*/



int main (){
  
  //comment when reading from stinput
  int n=13;
  double X[]={3 , 3.1 , 3.2 , 3.3 , 3.4 , 3.5 , 3.6, 3.7, 3.8, 3.9, 4, 4.1, 4.2};
  //  double F[]={8.818277,8.688986,8.445859,8.086761,7.617084,7.049787};
  double F[n];
  
  /*
    int n;
    scanf("%d",&n);
    double X[n];
    for(int i=0;i<n;++i)scanf("%lf",&X[i]);
  */
  double ans=0,h=0;  
  for(int i=0;i<n;F[i]=fun(X[i++])); //llenamos las f(xn)
  
  printf ("trapecio sencillo -----> ");  
  ans= (X[n-1]-X[0])*((F[0]+F[n-1])/2);//error = (f''(zi)/12) * (b-a)^3
  printf("%lf \n\n",ans);


  printf ("trapecio generalizado -> ");
  h=(X[n-1]-X[0])/(n-1); //(b-a)/n
  ans=0;
  for(int i=1;i<n-1;ans+=F[i++]);
  ans=(0.1/2.0)*(F[0]+(2*ans)+F[n-1]);
  printf("%lf \n\n",ans);

  
  printf("Simpson 1/3  ----------> ");//tres puntos igualmente espaciados -- cuidado al cambiar de num de puntos
  h=(X[n-1]-X[0])/2.0;//(b-a)/2
  ans=(h/3.0)*(F[0]+(4*F[(n-1)/2])+F[n-1]);//error= (-1/90)*h^5f^4(zi)
  printf("%lf \n\n",ans);
  //  for(int i=0;i<n;printf("%d -> %lg \n",i,F[i]),++i);
  
  printf("Simpson 1/3 Gen -------> ");//numero de puntos impar igualmente espaciados, salen un num de intervalos par 
  h=(X[n-1]-X[0])/(n-1);//(b-a)/n  
  double par=0,impar=0;
  for(int i=1;i<n-1;++i)
    if(i%2==0)
      par+=F[i];
    else
      impar+=F[i];
  par*=2;
  impar*=4;
  ans=(h/3.0)*(F[0]+impar+par+F[n-1]);//error= -(((b-a)^5)/180n^4)* f^(barra)^4 de (zi)
  printf("%lf \n\n",ans);


  printf("Simpson 3/8 -----------> ");//toma cuatro puntos igualmente espaciados --- cuidado al cambiar num de puntos
  ans=0;
  h=(X[n-1]-X[0])/3;
  ans=((3*h)/8)*(F[0]+3*(F[(n-1)/3])+3*(F[2*((n-1)/3)])+F[n-1]); //error = -((b-a)^5/6480)*f^4(zi)
  printf("%lf \n\n",ans);
  
  return 0;
}
