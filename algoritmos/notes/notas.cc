/* 
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "notas.h"
*/
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
/*
  Sistemas lineales de ecuaciones 
  Ax=b -> Ub'->x
  
  ** Eliminación Gaussiana
    mik = aix/akk
    fi = fi -mik*fk
    aij = aij - mik*akj
    1<=K<=n
    k+1<=i<=n
    k<=j<=n+1
  ** tecnicas de pivoteo parcial, total, escalonado
     Razones
     *Algun aii = 0 q no se logre eliminar con intercambio de filas
     *Redondeo por el numero de operaciones
    Estas tecnicas se usan para evitar que se hagan divisiones por numeros muy cercanos a cero
    Evitar overflow
    Todas las tecnicas intentan hacer Mik <=1
    Pivoteo total x1 el aii lo mayor posible al momento de despejar
  ** Factorización matrices 
     Toda matriz A se puede hacer A=LDU
     => Ax=b => LUx=b sea Ux=z entonces Lz=b
     C = Uii = 1
     D = Lii = 1
     Cholesky : Uii = Lii
     Siempre lo primordial es calcular el termino de la diagonal para calcular los demas terminos
     
     MACRO Algoritmo
     lee A // Sin b
     HallarLU(A,n): L,U
     Determinante(A) = DET(L)*DET(U) = Diag(L)*Diag(U)
     while(lee b)
       sus_progresiva(L,b):Z
       sus_regresiva(U,z):X
       Muestre X

  ** Matrices especiales
    Banda
    Simetrica
    Estrictamente dominante diagonalmente(que la suma de todos los terminos menos el de la diagonal en valor absoluto es menor que el termino de la diagonal en valor absoluto) -> Es no singular
    Positiva Definida: si x^tAx>0 y simetrica -> Es no singular
    
  ** Iterativos
    Jacobi : x = D^-1(L+U)x + D^-1(b)
    Gauss-seidel : x = (D-L)^-1Ux + (D-L)^-1(b)
    xi = (bi - SUM(AipXp) - SUM(AirXr))/Aii
    alfa = 1 Si converge rapido
    alfa > 1 Si converge lento
    0<alfa<1 Si no converge
    r = b - b*
    K = condiocinal(A) = ||A||*||A^-1||
    ||x-x'|| <= k||r||/||A||
    ||x-x'||/||x|| <= k||r||/||b||
    K ~~ ||r||/||y||10^t
    y es solucion de Ay=r y t # de digitos
    
    ** Polinomio Caracteristico(alfa) = det(A-alfaI)
    Las Raices de este  polinomio se llaman valores propios

    El radio espectral de una matriz A
           p(A) = max(alfa)
	   Prop.
	   p(A)<=||A||
	   Si p(T)<= 1 los iterativos convergen
	   
  ** Gauss - Jordan AI-> IX
   Dos veces eliminacion gaussiana
  
 */
int main()
{

  return 0;
}
