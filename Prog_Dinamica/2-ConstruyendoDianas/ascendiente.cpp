
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
Inicialmente tenemos el valor objetivo al que queremos llegar O dandole a las dianas.
Tenemos por un lado, un vector que contiene las diferentes secciones de la diana, es 
decir, los diferentes valores de las dianas. 

   int O;
   vector<int> D();

Leemos los valores por la entrada estándar.

El problema se resuelve mediante la siguiente función recursiva:

donde i son las dianas disponibles y j es la cantidad objetivo

dianas(i, j) = dianas(i-1, j)                                      si D[i] > j
               min(dianas(i-1, j), dianas(i, j - D[i]) + 1)        si D[i] <= j

0 <= i <= O
0 <= j <= D.size()

Caso básico: dianas(i, 0) = 0       si j == 0 significa que hemos llegado a una solución independientemente del valor de i
             dianas(0, j) = INFINTO  -> NO PODEMOS LLEGAR A ESA PUNTUACIÓN

Llamada Inicial: dianas(n, O)       donde n es el número de dianas disponibles

El rellenado de la matriz lo haré de forma ascendiente e iterativa.

Finalmente, construimos la solución. Para ello, necesitamos la matriz completa y no podemos optimizar en espacio.

// CORRECCIÓN: SI QUE SE PUEDE OPTIMIZAR EN ESPACIO MEDIANTE UN VECTOR

*/

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <vector>
using namespace std;

struct Solucion{
   EntInf sol;
};
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Solucion resolver(const vector<int>& D, const int& O, const int& n, Matriz<EntInf>& matriz) {
   matriz[0][0] = 0;
   for (int i = 1; i <= n; i++)
   {
      matriz[i][0] = 0;
      for (int j = 1; j <= O; j++)
      {
         int diana = D[i-1];
         if(diana > j){
            matriz[i][j] = matriz[i-1][j];
         }
         // Aquí diana <= j -- se puede pillar esa diana
         else{
            matriz[i][j] = min(matriz[i-1][j], matriz[i][j-diana] + 1);
         }
      }
      
   }
   return {matriz[n][O]};

}

using camino = vector<int>;

camino reconstruir(const Matriz<EntInf>& matriz, const vector<int>& D, int n, int O){
   camino sol;

   if(matriz[n][O] != Infinito){
      int i = n, j = O;
      while(j > 0){
         if(D[i-1] <= j && matriz[i][j] != matriz[i-1][j]){
            sol.push_back(D[i-1]);
            j = j - D[i-1];
         }
         else{
            --i;
         }
      }
   }
   return sol;
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int O, n; 
   cin >> O >> n;
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   vector<int> D(n);
   for (int i = 0; i < n; i++)
   {
      cin >> D[i];
   }
   
   Matriz<EntInf> matriz(n+1, O+1, Infinito);

   Solucion sol = resolver(D, O, n, matriz);
   if(sol.sol != Infinito){
      sol.sol.print();
      cout << ": ";
      camino reconstruccion = reconstruir(matriz, D, n, O);
      for (int i = 0; i < reconstruccion.size(); i++)
      {
         cout << reconstruccion[i] << " ";
      }
      
      cout << endl;
   }
   else{
      cout << "Imposible" << endl;

   }

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
