#include <cstdio>
#include <math.h>
#define TOLERANCIA 7
using namespace std;


double val_min = 1.0*(pow(10,-1*TOLERANCIA));

struct intervalo{
  double xini, xfin;
  int tipo;
  intervalo(){}
  intervalo(double low, double high, int type): xini(low), xfin(high), tipo(type){}
};

double P_dado_A1(double i, double ig, int n){
  
  if(fabs(i - ig) < val_min){
    printf("la diferencia entre los dos parámetros es: %lf\n", i-ig);
    return n/(1+i);
  }else{
    i /=100; //paso de las tasas de porcentaje a valor decimal.
    ig/=100;

    printf("entro por el otro lado\n");    
    double factor = pow((1.0 + ig)/(1.0+i), n);
    double cociente = (1.0-factor) / (i-ig);
    return cociente;

  }
}

double funcion(double xini){
double resultado = pow(xini, 2)-2;
 return resultado;
}

// la signatura para el metodo es como sigue
// 0: se encontro una raiz
// 1: se encontro intervalo
//-1: no se encontro
intervalo busquedas_incrementales(double Xo, double delta, int max_ite){

  int contador = 0;
  double y = funcion(Xo);
  double y_siguiente = y;
  printf("iteracion    Xo    f(Xo)\n");
  printf("%d          %lf   %lf\n", contador, Xo, y_siguiente);
  while(fabs(y) > val_min && fabs(y_siguiente) > val_min && y*y_siguiente > 0.0 && contador < max_ite){ 
    y = y_siguiente;
    Xo += delta;
    contador ++;
    y_siguiente = funcion(Xo);
    printf("%d          %lf   %lf\n", contador, Xo, y_siguiente);
  }
  //comprobaciones:
  if(fabs(y) < val_min){
    intervalo i(Xo-delta, 0.0, 0);
    return i;
  }else{
    if(fabs(y_siguiente) < val_min){
      intervalo i(Xo, 0.0, 0);
      return i;
    }else{
      if(y*y_siguiente < 0.0){
	intervalo i (Xo-delta, Xo, 1);
	return i;
      }else{
	if(contador >= max_ite){
	intervalo i(0.0,0.0,-1);
	return i;
	}else{
	  intervalo i(0.0,0.0,2);
	  return i;
	}
      }//fin max_ite
    }//fin intervalo con tolerancia
  }//fin y_siguiente raiz
}//fin busquedas incrementales


double biseccion(double xmin, double xmax, int max_ite, double tolerancia){


}


int main(){
  while(true){
    double pinicial, delta;
    int max_iteraciones;
    //printf("valor tolerancia: %3.10f\n", val_min);
    printf("Ingrese los datos para busquedas incrementales \n");
    printf("Ingrese punto inicial:\n");
    scanf("%lf", &pinicial);
    printf("Ingrese delta:\n");
    scanf("%lf", &delta);
    printf("Ingrese max iteraciones: \n");
    scanf("%d", &max_iteraciones);
    printf(" pinicial: %lf\n delta:%lf\n maxite: %d\n", pinicial, delta, max_iteraciones);
    intervalo i = busquedas_incrementales(pinicial, delta, max_iteraciones);
    if(i.tipo == 0){
      printf("Se encontró raiz en : %lf\n\n", i.xini);
    }else{ 
      if(i.tipo == 1){
	printf("Raiz en el intervalo: [%lf, %lf] \n\n", i.xini, i.xfin);
      }else{
	if(i.tipo == -1)
	  printf("No se encontro cambio de signo en %d iteraciones\n\n", max_iteraciones);
      }
    }
  }
  return 0;
}
