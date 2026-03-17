
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
   Vamos a utilizar una implementación descendiente utilizando una matriz. Los datos de entrada serán:
   la palabra a procesar. 

   aibofobia(i,j) = mínimo número de letras a añadir para construir un palíndromo dada la palabra inicial, 
                     siendo i el índice que representa el caracter de la parte izquierda 
                     y j el índice que representa el caracter de la parte derecha
                     0 <= i <= j < palabra.size()

   aibofobia(i,j) = aibofobia(i+1,j-1)                               si palabra[i] == palabra[j]
                    min(aibofobia(i+1,j), aibofobia(i, j-1)) + 1     si palabra[i] != palabra[j]

   aibofobia(i,j) = 0         si i >= j
   
   llamada inicial: aibofobia(i, palabra.size()-1)
*/

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <vector>

using namespace std;


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
EntInf resolver(const string& palabra, Matriz<EntInf>& m, int i, int j) {
   if(i >= j){
      return 0;
   }
   if(m[i][j] != Infinito){
      return m[i][j];
   }
   else{
      if(palabra[i] != palabra[j]){
         m[i][j] = min(resolver(palabra, m, i+1, j), resolver(palabra, m, i, j-1)) + 1;
      }
      else{
         m[i][j] = resolver(palabra, m, i+1, j-1);
      }
      return m[i][j];
   }
}

void reconstruir(const string& palabra, Matriz<EntInf>& m, int i, int j, string& res){
   if(i > j) return;
  
   if(palabra[i] == palabra[j]){
      if(i == j){
         res.push_back(palabra[i]);
      }
      else{
         res.push_back(palabra[i]);
         reconstruir(palabra, m, i+1, j-1, res);
         res.push_back(palabra[j]);
      }
   }
   
   if(m[i+1][j] < m[i][j-1]){
      res.push_back(palabra[i]);
      reconstruir(palabra, m, i+1, j, res);
      res.push_back(palabra[i]);
   }
   else{
      res.push_back(palabra[j]);
      reconstruir(palabra, m, i, j-1, res);
      res.push_back(palabra[j]);
   }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   string palabra;  

   if(!(cin >> palabra)){
      return false;
   }
   int n = palabra.size();
   Matriz<EntInf> m(n, n, Infinito);
   EntInf result = resolver(palabra, m, 0, n-1);
   string sol = "";
   reconstruir(palabra, m, 0, n-1, sol);
   
   if(result != Infinito){
      result.print();
      cout << " " << sol << endl;
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
