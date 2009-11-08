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


double biseccion(double xmin, double xmax, int max_ite){
 
  double ymin = funcion(xmin);
  double ymax = funcion(xmax);
  int contador = 0;
  double error = 1+val_min;
  if(ymin * ymax > 0.0){
    printf("Intervalo erroneo\n");
    return 0.0;
  }

  FILE *file;
  file = fopen("reporte_regla_falsa.txt", "a+");
  fprintf(file, "Ite\txmin\tf(xmin)\txmax\tf(xmax)\txm\tf(xm)\terror\n");
 
  printf("Ite\t   xmin\t          f(xmin)\t    xmax\t   f(xmax)\t   xm\t          f(xm)\t       error\n");

  double xm = xmin-(ymin*(xmin - xmax)/(ymin-ymax));
  while(ymin != 0.0 && ymax != 0.0 && error > val_min && contador < max_ite){
    double ym = funcion(xm);
    printf("%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%E\n", contador, 
	   xmin, ymin, xmax, ymax, xm, ym, error);
    fprintf(file,"%d\t%1.10f\t%1.10f\t%1.10f\t%1.10f\t%1.10f\t%1.10f\t%E\n", contador, 
	   xmin, ymin, xmax, ymax, xm, ym, error);
    if(ym*ymin < 0.0){
      xmax = xm;
      ymax = ym;      
    }else if(ym*ymax < 0.0){
      xmin = xm;
      ymin = ym;
    }
    error = fabs(xmin-xmax); //error absoluto
    xm = xmin-(ymin*(xmin - xmax)/(ymin-ymax));
    contador++;
  }
  fprintf(file, "----------------------------------\n");
  fclose(file);
  if(ymin == 0.0){
    printf("raiz a en %lf\n", xmin);
    return xmin;
  }else if(ymax == 0.0){
    printf("raiz b en %lf\n", xmax);
    return xmax;
  }else if(error <=  val_min){
    printf("raiz en %3.10f con tolerancia %E\n", xm, val_min);
    return xm;
  }else {
    printf("no se encontro raiz en %d iteraciones\n", max_ite);
    return 0.0;
  }
  
}

  int main(){
    while(true){
      double xmin, xmax;
      int max_ite, precision;
      printf("Metodo regla falsa\n");
      printf("Ingrese precision:\n");
      scanf("%d", &precision);
      val_min = pow(10.0, -precision);
      printf("Ingrese Xinicial:\n");
      scanf("%lf", &xmin);
      printf("Ingrese Xfinal:\n");
      scanf("%lf", &xmax);
      printf("Ingrese max iteraciones:\n");
      scanf("%d", &max_ite);
      double d = biseccion(xmin, xmax, max_ite);
      printf("%lf", funcion(d));
    }
  return 0;
}
