#include <cstdio>
#include <math.h>

#define TOLERANCIA 7

using namespace std;

double val_min = 1.0*(pow(10, -1*TOLERANCIA));

//aqui se cambia la funcion
double funcion(double x){
  double resultado = pow(x, 2)-2;
  return resultado;
}

double g(double x){
  return pow(x, 3)/2;
}


double punto_fijo(double xinicial, int max_ite){
  double y = funcion(xinicial);
  double error = 1+val_min;
  int contador = 0;
  FILE *file;
  file = fopen("reporte_punto_fijo.txt", "a+");
  printf("ite\tXo\tg(Xo)\tf(Xo)\terror\n");
  fprintf(file, "ite\tXo\tg(Xo)\tf(Xo)\terror\n");
  printf("%d\t%1.10f\t%1.10f\t%1.10f\t----\n", contador,xinicial,g(xinicial), y);
  fprintf(file, "%d\t%1.10f\t%1.10f\t%1.10f\t----\n", contador,xinicial,g(xinicial), y);
  while(y != 0.0 && error > val_min && contador < max_ite){
    double xaux = xinicial;
    xinicial = g(xinicial);
    y = funcion(xinicial);
    error = fabs(xaux-xinicial);
    contador++;
    printf("%d\t%1.10f\t%1.10f\t%1.10f\t%E\n", contador,xaux,xinicial, y, error);
    fprintf(file,"%d\t%1.10f\t%1.10f\t%1.10f\t%E\n", contador,xaux,xinicial, y, error);
  }
  if(y == 0.0){
    printf("raiz en %1.10f\n", xinicial);
    fprintf(file,"raiz en %1.10f\n", xinicial);
    fprintf(file, "_____________________\n");
    fclose(file);
    return xinicial;
  }else if(error <= val_min){
    printf("raiz %1.10f con tolerancia %E val_min\n", xinicial, val_min);
    fprintf(file,"raiz %1.10f con tolerancia %E val_min\n", xinicial, val_min);
    fprintf(file, "_____________________\n");
    fclose(file);
    return xinicial;
  }else{
    printf("no se encontro raiz luego de %d iteraciones\n", max_ite);
    fprintf(file, "no se encontro raiz luego de %d iteraciones\n", max_ite);
    fclose(file);
    return 0.0;
  }           
}

int main(){
  while(true){
    double xini;
    int max_ite, precision;
    printf("Metodo punto fijo\n");
    printf("Ingrese precision:\n");
    scanf("%d", &precision);
    val_min = pow(10.0, -precision);
    printf("Ingrese Xinicial:\n");
    scanf("%lf", &xini);
    printf("Ingrese max iteraciones:\n");
    scanf("%d", &max_ite);
    double d = punto_fijo(xini, max_ite);
    printf("%lf", funcion(d));
  }
  return 0;
}
