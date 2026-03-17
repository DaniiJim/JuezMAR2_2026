
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*

La entrada de nuestro programa será el tamaño de la matriz N y una matriz cuadrada C[N][N] en la que guardaremos los valores. 

Haremos una versión de programación dinámica ascendiente, rellenando dos vectores, uno manteniendo con los valores de la fila anterior, 
inicialmente con la primera fila del tablero y otro que contendrá la suma acumulada.
La idea es empezar por la segunda fila, buscando maximizar la suma acumulada, es decir, la máxima cantidad que se puede conseguir
en esa celda teniendo en cuenta las anteriores y la cantidad de la celda actual. El rellenado del vector es indiferente, se puede 
rellenar de derecha a izquierda o de izquierda a derecha, siendo esta última la forma en la que lo voy a plantear, ya que en ambas es
necesario usar un vector auxiliar para guardar los valores de la fila anterior.


maximizarCelda(i, j) = cantidad máxima que podemos obtener con los valores de la matriz teniendo en cuenta desde las filas 0 hasta i
y las columnas 0 hasta j.

La función recursiva tiene la siguiente forma: 

maximizarCelda(i, j) = max(maximizarCelda(i-1, j-1), maximizarCelda(i-1, j), maximizarCelda(i-1, j+1)) + C[i][j] si 0 < j < N-1 e i > 0 
                     = max(maximizarCelda(i-1, j), maximizarCelda(i-1, j+1)) + C[i][j] si j == 0 e i > 0
                     = max(maximizarCelda(i-1, j-1), maximizarCelda(i-1, j)) + C[i][j] si j == N-1 e i > 0

donde             0 <= i < N  &&  0 <= j < N    donde N es el # de filas y columnas (matriz cuadrada)

Llamada inicial: maximizarCelda(0,0)   Para que vaya calculando de forma ascendiente todos los valores

Caso básico: maximizarCelda(0, j) = C[0][j]     Si i = 0 significa que hemos llegado a la fila inicial
                                                por lo que los valores de nuestro vector son los propios valores de la matriz.
            
 puedo evitar usar dos vectores, uso una variable auxiliar para guardar el valor que machaco.
*/

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <vector>
using namespace std;

struct Solucion{
   int sol;
   int columna;
};
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Solucion resolver(const  Matriz<int>& C, const int& N) {
   //vector<int> filaAnterior(N);
   int valorPrevio;
   vector<int> sumaAcumulada(N, 0);

   sumaAcumulada = C[0];      

   for (int i = 1; i < N; i++)
   {
      for (int j = 0; j < N; j++)
      {
         if(j == 0){
            valorPrevio = sumaAcumulada[j];
            sumaAcumulada[j] = max(sumaAcumulada[j], sumaAcumulada[j+1]) + C[i][j];

         }
         else if (j == N-1){
            sumaAcumulada[j] = max(sumaAcumulada[j], valorPrevio) + C[i][j];
         }
         else{
            // valorPrevio = sumaAcumulada[j+1];
            sumaAcumulada[j] = max(valorPrevio, sumaAcumulada[j]);
            sumaAcumulada[j] = max(sumaAcumulada[j], sumaAcumulada[j+1]) + C[i][j];
         }
      }
   }
   // Bucle para encontrar la suma máxima y la columna en la que está
   
   Solucion solucion;

   solucion.sol = sumaAcumulada[0];
   solucion.columna = 0;
   for (int k = 1; k < N; k++)
   {
      if(sumaAcumulada[k] > solucion.sol){
         solucion.sol = sumaAcumulada[k];
         solucion.columna = k;
      }
   }
   
   return solucion;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int N;  
   cin >> N;
   
   if (!std::cin)  // fin de la entrada
      return false;

   Matriz<int> C(N, N);

   for (int i = 0; i < N; i++)
   {
      for (int j = 0; j < N; j++)
      {
         int aux;
         cin >> aux;
         C[i][j] = aux;
      } 
      
   }
   
   Solucion miSolucion = resolver(C, N);

   cout << miSolucion.sol << " " << miSolucion.columna + 1 << '\n';

   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
