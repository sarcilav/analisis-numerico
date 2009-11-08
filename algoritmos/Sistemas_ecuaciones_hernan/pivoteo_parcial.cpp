#include <cstdio>
#include <cstdlib>
#include <math.h>
using namespace std;


//encapsulamiento de una matriz para uso en eliminacion gaussiana
struct matriz
{
  int n, m; //número de filas y columnas de la matriz
  double** p; //puntos de la ecuación
      
  matriz(){}
  //inicializa una matriz vacia de las dimensiones solicitadas
  matriz(int ni,int  mi){
    n = ni;
    m = mi;
    p = new double*[ni];
    for (int i = 0; i < ni; i++)
      {
	p[i] = new double[mi];
      }
  }

};


//lee una matriz que ya tenga definidos el numero de filas y de columnas
void leer_matriz(matriz *entrada){
  double aux;
  for(int i = 0; i < entrada->n; ++i)
    {
      for(int j = 0; j < entrada->m; ++j)
	{
	  scanf("%lf", &aux);
	  entrada->p[i][j] = aux;
	}
    }        
}


//imprime una matriz que se le pase como parametro
void imprimir(matriz in){
  printf("impresion de la matriz n con %d filas y %d columnas\n", in.n, in.m);
  for(int i = 0; i < in.n; ++i){
    for(int j = 0; j < in.m; ++j){
      printf("%lf ", in.p[i][j]);
    }
    printf("\n");
  }
}



//hace pivoteo parcial para garantizar que elemento de la diagonal es el mayor
void piv_parcial(matriz * in, int k) //k = etapa a la que se le busca el mayor
{
  double mayor = 0.0;
  int fila = k;
  for(int i = k; i < in->n; ++i)//se encuentra el mayor de las filas
    {
      if(fabs(in->p[i][k]) > mayor)
	{
                           printf("\n mayor: %lf dentro del metodo --- %lf\n\n", mayor, fabs(in->p[i][k]));
	  mayor = fabs(in->p[i][k]);
	  fila = i;
	}
    }
  
  printf("--------mayor : %lf, de la etapa: %d en la fila: %d\n", mayor, k, fila);
  imprimir(*in);
  if(k != fila)
    {
      for(int i = 0; i < in->m; ++i){
	double aux = in->p[k][i];
	in->p[k][i] = in->p[fila][i];
	in->p[fila][i] = aux;  
      }
    }
  
}


//hace la eliminacion gaussiana de una matriz y retorna la matriz
//de multiplicadores
matriz eliminacion_gaussiana(matriz *mext){
  if(mext->n+1 != mext->m){
    printf("error, la matriz no es una matriz extendida\n");
    matriz m;
    return m;
  }else{
    //matriz de multiplicadores
    matriz m(mext->n, mext->m);
    for(int k = 0; k < mext->n-1; ++k){
      piv_parcial(mext, k);
      for(int i = k+1; i < mext->n; ++i){
	m.p[i][k] = mext->p[i][k]/mext->p[k][k];
	for(int j = k; j < mext->m; ++j){
	  mext->p[i][j] -=(m.p[i][k]*mext->p[k][j]);
	}
      }
    }
    return m;
  }

}

//sustituye de la ultima variable hasta la primera
//retorna una matriz de 1 X n (numero de variables)
matriz sustitucion_regresiva(matriz in){
  
  matriz r (1, in.n);
  for(int k = in.n-1; k >= 0; --k){
    double acum = 0.0;
    //sumatoria interna de terminos
    for(int i = k+1; i < in.n; ++i){
      acum += (in.p[k][i]*r.p[0][i]);
    }
    r.p[0][k] = (in.p[k][in.n] - acum)/in.p[k][k]; //b_i - sumatoria
  }

  return r;

}

//sustituye de la primera variable hasta la ultima
//retorna una matriz de 1 X n (numero de variables)
matriz sustitucion_progresiva(matriz in){
  matriz r (1, in.n);
  for(int k = 0; k<= in.n-1; ++k){
    double acum = 0.0;
    //sumatoria interna de términos
    for(int i = 0; i < k-1; ++i){
      acum += (in.p[k][i]*r.p[0][i]);
    }
    r.p[0][k] = (in.p[k][in.n] - acum)/in.p[k][k]; //b_i - sumatoria
  }
  return r;
} 








int main()
{
  int filas, columnas;
  printf("ingrese el numero de filas y columnas\n");
  scanf("%d %d", &filas, &columnas);
  printf("ingrese la matriz por filas separadas por espacio\n");
  matriz entrada(filas, columnas);
  leer_matriz(&entrada);
   matriz m;
   m = eliminacion_gaussiana(&entrada);
   printf("\n\nmatriz de multiplicadores\n\n");
   imprimir(m);
   printf("matriz luego de la eliminacion gaussiana\n");
   imprimir(entrada);
   matriz resultados = sustitucion_regresiva(entrada);
   printf("resultados a las ecuaciones: \n");
   imprimir(resultados);
   //entrada();
  //eliminacionGaussiana();
  //imprimir();
  system("PAUSE");
  return EXIT_SUCCESS;
  //return 0;
}
