
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
Para la entrada del programa, usaremos una variable entera N que indica el # de tipos de bombilla, un vector de potencias de tamaño N
y un vector de costes de tamaño N.

Haremos una versión de programación dinámica ascendiente. 

   lucesFiesta(i, j) = menor coste para cumplir la restricción con bombillas de la 0 a la i y 
                        potencia que va de 0 a j. 0 <= j <= maxPower   0 <= i < N




   lucesFiesta(i, j) = lucesFiesta(i-1, j)                        si potencias[i] > j
                       lucesFiesta(i, j-potencias[i-1])           si potencias[i] <= j



   
*/

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <vector>
using namespace std;

struct Estado{
   EntInf coste;
   int potencia;
};

bool mejor(const Estado& a, const Estado& b){
   if(a.coste != b.coste){
      return a.coste < b.coste;
   }
   return a.potencia < b.potencia;
}



// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Estado resolver(const vector<int> potencias, const vector<int> costes, int N, int maxPower, int minPower) {
   Estado peor = {Infinito, -1};
   Matriz<Estado> m(N+1, maxPower+1, peor);

   m[0][0] = {0, 0};
   for (int i = 1; i <= N; i++)
   {
      m[i][0] = {0,0};
      for (int j = 1; j <= maxPower; j++)
      {
         m[i][j] = m[i-1][j];

         if(potencias[i-1] <= j && m[i][j - potencias[i-1]].coste != Infinito){
            Estado candidato;
            candidato.coste = m[i][j-potencias[i-1]].coste + EntInf(costes[i-1]);
            candidato.potencia = m[i][j-potencias[i-1]].potencia + potencias[i-1];

            if(mejor(candidato, m[i][j])){
               m[i][j] = candidato;
            }

         }
      }
      
   }
   Estado sol = {Infinito, -1};
   for (int i = minPower; i <= maxPower; i++)
   {
      if(mejor(m[N][i], sol))
         sol = m[N][i];
   }
   

   
   return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int N, maxPower, minPower;  

   if(!(cin >> N >> maxPower >> minPower)){
      return false;
   }

   vector<int> potencias(N);
   vector<int> costes(N);
   
   for (int i = 0; i < N; i++)
   {
      cin >> potencias[i];
   }
   for (int j = 0; j < N; j++)
   {
      cin >> costes[j];
   }

   Estado sol = resolver(potencias, costes, N, maxPower, minPower);

   if(sol.coste == Infinito){
      cout << "IMPOSIBLE" << endl;
   }
   else{
      cout << sol.coste << " " << sol.potencia << endl;
   }
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
// #ifndef DOMJUDGE
//    std::ifstream in("casos.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
// #endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
// #ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//    system("PAUSE");
// #endif
   return 0;
}
