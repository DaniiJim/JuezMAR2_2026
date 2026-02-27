#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
#include "EnterosInf.h"
#include <sstream>


using namespace std;
using lli = long long int;

int maxFood(vector<int>& cubes) {
    int n = cubes.size();
    if (n == 0) return 0;

    Matriz<int> dp(n,n, 0);

    for (int i = 0; i < n; ++i) {
        dp[i][i] = cubes[i]; // Si solo queda un cubo, la vaca lo come
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            
            // La vaca elige el cubo más a la izquierda
            int pickLeft = cubes[i];
            if (i + 2 <= j) { // Aseguramos que hay al menos 2 cubos restantes
                if ( cubes[i+1] > cubes[j]) {
                    pickLeft += dp[i + 2][j];
                }else{
                    pickLeft += dp[i + 1][j - 1];
                }
                

                    
            }

            // La vaca elige el cubo más a la derecha
            int pickRight = cubes[j];
            if (i + 1 <= j - 1) { // Aseguramos que hay al menos 2 cubos restantes
               if(cubes[i] < cubes[j-1]){
                    pickRight += dp[i][j - 2];
               }else{
                    pickRight += dp[i + 1][j - 1];
               }
                
            }

            dp[i][j] = max(pickLeft, pickRight);  // i es  el inicio y j es el final del intervalo de cubos que quedan por comer 
        }
    }

    return dp[0][n - 1];
}

bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;

    vector<int> cubes(n);
    for (int i = 0; i < n; ++i) {
        cin >> cubes[i];
    }

    int maxFoodAmount = maxFood(cubes);
    cout << maxFoodAmount << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std :: cin to casos .
#endif
    //int numCasos;
    //cin >> numCasos;
    //for (int i = 0; i < numCasos; ++i)
    //{
    //    resuelveCaso(); std::cin.ignore();
    //}
    while (resuelveCaso()) {

    }
    // Para restablecer entrada . Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system(" PAUSE ");
#endif
    return 0;

}
