
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
Para la entrada del programa, usaremos una variable entera capacidadOx que indica la cantidad de oxigeno de la bombona, después una variable numCofres que será
el número de cofres que hay para elegir, seguido del vector de pares tesoros {profundidad, premio}.

Haremos una versión de programación ascendente.


cazatesoros(i, j) = recompensa máxima posible teniendo en cuenta los primeros i cofres teniendo capacidad de bombona j

cazatesoros(i, j) = cazatesoros(i-1, j)                                                               si 3*tesoros[i].profundidad > j
                  = max(cazatesoros(i-1, j-3*tesoros[i-1].profundidad), cazatesoros(i-1, j))          si 3*tesoros[i].profundidad <= j


Llamada inicial = cazatesoros(numCofres, capacidadOx)

Casos base:   cazatesoros(i, 0) = 0
              cazatesoros(0, j) = 0
  


   
*/

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Cofre{
   int profundidad;
   int recompensa;
};



// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(const vector<Cofre>& tesoros, const int& numCofres, const int& capacidadOx, Matriz<int>& m) {
   
   m[0][0] = 0;
   for (int i = 1; i <= numCofres; i++)
   {
      m[i][0] = 0;
      for (int j = 1; j <= capacidadOx; j++)
      {
         if(3*tesoros[i-1].profundidad > j){
            m[i][j] = m[i-1][j];
         }
         else{
            m[i][j] = max(m[i-1][j], m[i-1][j-3*tesoros[i-1].profundidad] + tesoros[i-1].recompensa);          
         }
      }
   }
   return m[numCofres][capacidadOx];
}

vector<Cofre> reconstruir(const Matriz<int>& m, const vector<Cofre>& tesoros, int numCofres, int capacidadOx){
   int j = capacidadOx;
   vector<Cofre> elegidos;
   for (int i = numCofres; i >= 1; --i)
   {
      if(m[i][j] != m[i-1][j]){
         elegidos.push_back(tesoros[i-1]);
         j = j - 3*tesoros[i-1].profundidad;
      }
   }
   return elegidos;
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int numCofres, capacidadOx;  

   if(!(cin >> capacidadOx >> numCofres)){
      return false;
   }

   vector<Cofre> tesoros(numCofres);
    
   
   for (int i = 0; i < numCofres; i++)
   {
      Cofre aux;
      cin >> aux.profundidad >> aux.recompensa;
      tesoros[i] = aux;
   }
   Matriz<int>m (numCofres+1, capacidadOx+1, 0);
   int sol = resolver(tesoros, numCofres, capacidadOx, m);

   if(sol != 0){
      vector<Cofre> camino = reconstruir(m, tesoros, numCofres, capacidadOx);
      cout << sol << endl;
      int elegidos = camino.size();
      cout << elegidos << endl;
      for (int i = elegidos-1; i >= 0; --i)
      {
         cout << camino[i].profundidad << " " << camino[i].recompensa << endl;
      }
   }
   else{
      cout << "0" << endl;
      cout << "0" << endl;
   }
   cout << "---" << endl;

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
