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

//sustituye de la ultima variable hasta la primera
//retorna una matriz de 1 X n (numero de variables)
matriz sustitucion_regresiva(matriz in){
  
  matriz r (1, in.n);
  for(int k = in.n-1; k >= 0; --k){
    double acum = 0.0;
    //sumatoria interna de términos
    for(int i = k+1; i < in.n; ++i){
      acum += (in.p[k][i]*r.p[0][i]);
    }
    r.p[0][k] = (in.p[k][in.n] - acum)/in.p[k][k]; //b_i - sumatoria
  }

  return r;

}

//le agrega una fila (la de resultados) al final a una matriz desde la entrada

matriz append_in(matriz a){
  matriz result(a.n, a.m+1);
  double entrada;
  for(int i = 0; i < a.n ; ++i)
    {
      for(int j = 0; j < a.m+1; ++j)
	{
	  if(j == a.m)
	    scanf("%lf", &result.p[i][j]);
	  else
	    result.p[i][j] = a.p[i][j];
	}  
    }  
  return result;
}

//le agrega una columna de otra matriz

matriz append_m(matriz a, matriz res)
{
  matriz result(a.n, a.m+1);
  if(res.n == 1) //se ingresa resultados como vector fila
    {
      for(int i = 0; i < a.n ; ++i)
	{
	  for(int j = 0; j < a.m+1; ++j)
	    {
	      if(j == a.m)
		result.p[i][j] = res.p[0][i];
	      else
		result.p[i][j] = a.p[i][j];
	    }  
	}  
      return result;      
    }
  else if(res.m == 1) //se ingresa resultados como vector columna
    {
      for(int i = 0; i < a.n ; ++i)
	{
	  for(int j = 0; j < a.m+1; ++j)
	    {
	      if(j == a.m)
		result.p[i][j] = res.p[i][0];
	      else
		result.p[i][j] = a.p[i][j];
	    }  
	}  
      return result;                
    }
  else
    {
      printf("error, para agregarle una fila a una matriz, es necesario que sea vector fila o columna\n");
      return result;
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


/*factorizacion de matrices por el metodo de cholesky
 *recibe las dos matrices vacias (l, u) en las que van a quedar los terminos
 *y la matriz que se desea factorizar (a)
 *modifica l, u
 */
void fact_cholesky(matriz* l, matriz *u, matriz a){

  if(l->n != l->m && u->n != u->m && a.n != a.m && l->n != u->n && u->n != a.n)    
      printf("\nerror: las matrices ingresadas a cholesky deben ser todas cuadradas y del mismo tamano\n\n");  
  else
    {
      for(int k = 0; k < a.n; ++k)//etapas
	{ 
	  double acum1 = 0.0; //acumulador para la diagonal
	  for(int j = 0; j < k-1; ++j)//sumatoria para diagonal
	    acum1 += l->p[k][j]*u->p[j][k];
	  
	  l->p[k][k]=sqrt(a.p[k][k]-acum1); //calcula la diagonal
	  u->p[k][k] = l->p[k][k];          //iguala los terminos en ambas matrices
	  
	  for(int i = k+1; i < a.n; ++i)//recorrido de las columnas
	    {
	      double acum2 = 0.0;
	      double acum3 = 0.0;
	      for(int j = 0; j < a.n; ++j)//calculo de las sumatorias para la L y la U
		{
		  acum2 += l->p[i][j]*u->p[j][k];
		  acum3 += l->p[k][j]*u->p[j][i];		  
		}
	      l->p[i][k] = (a.p[i][k] - acum2)/l->p[k][k];
	      u->p[k][i] = (a.p[k][i] - acum3)/u->p[k][k]; //l[k][k] = u[k][k]
	    }//fin recorrido columnas
      }//fin for etapas
    }
}


/*factoriza ya sea con el metodo de dolittle o con el de crault
 * si el parametro entero es un 1, factoriza por dolittle
 * si el parametro entero es un 0, factoriza por crault
 */
void fact_matriz(matriz* l, matriz* u, matriz a, bool dolittle){
if(l->n != l->m && u->n != u->m && a.n != a.m && l->n != u->n && u->n != a.n)    
      printf("\nerror: las matrices ingresadas a factorizacion deben ser todas cuadradas y del mismo tamano\n\n");  
  else
    {
      for(int k = 0; k < a.n; ++k)//etapas
	{ 
	  double acum1 = 0.0; //acumulador para la diagonal
	  for(int j = 0; j < k-1; ++j)//sumatoria para diagonal
	    acum1 += l->p[k][j]*u->p[j][k];
	  
	  if(dolittle)
	    u->p[k][k]=a.p[k][k]-acum1; //calcula la diagonal
	  else
	    l->p[k][k]=a.p[k][k]-acum1; //calcula la diagonal
	  
	  for(int i = k+1; i < a.n; ++i)//recorrido de las columnas
	    {
	      double acum2 = 0.0;//acumulador de las l
	      double acum3 = 0.0;// acumulador de las u
	      for(int j = 0; j < a.n; ++j)//calculo de las sumatorias para la L y la U
		{
		  acum2 += l->p[i][j]*u->p[j][k];
		  acum3 += l->p[k][j]*u->p[j][i];		  
		}
	      l->p[i][k] = (a.p[i][k] - acum2);

	      if(dolittle)
		l->p[i][k]/=u->p[k][k];

	      u->p[k][i] = (a.p[k][i] - acum3);

	      if(!dolittle)
		u->p[k][i]/= l->p[k][k];

	    }//fin recorrido columnas
	}//fin for etapas           
    }//fin else
}

//<=k-1 ////*********todo
int main()
{
  int tam; //tamaño del sistema que se va a trabajar
  int caso = 4; //tipo de factorizacion escogida por el usuario
  //1 para cholesky, 2 para dolittle, 3 para croult
  printf("ingrese el tamano del sistema de ecuaciones\n");
  scanf("%d", &tam);
  matriz l(tam, tam), u(tam, tam), a(tam, tam);
  printf("ingrese la matriz A por filas separadas por espacios\n");
  leer_matriz(&a);
  while(caso > 3 || caso <= 0)
    {
      printf("ingrese: \n1 para factorizar con cholesky\n2 para factorizar con dolittle\n3 para factorizar con croult\n");
      scanf("%d", &caso);
    }
  
  switch(caso)
    {
    case 1: 
      fact_cholesky(&l, &u, a);
      break;
    case 2:
      fact_matriz(&l, &u, a, true);
      for(int i = 0; i < l.n ; ++i)
	l.p[i][i] = 1.0;
      break;
    case 3:
      fact_matriz(&l, &u, a, false);
      for(int i = 0; i < l.n ; ++i)
	u.p[i][i] = 1.0;
      break;
    }   
  printf("resultado de la factorizacion de la matriz:\n\n");
  printf("resultado matriz l:\n\n");
  imprimir(l);
  printf("\n resultado de la matriz u:\n\n");
  imprimir(u);
  while(true)
    {
      printf("ingrese vector de resultados\n");
      matriz z = append_in(l);
      z = sustitucion_progresiva(z);
      matriz x = append_m(u, z);
      x = sustitucion_regresiva(x);
      printf("resultados:\n");
      imprimir(x);      
     }
  return 0;
}
