#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <unordered_map>


using namespace std;
using lli = long long int;

EntInf minimo_esfuerzo(int L, vector<int>& cuts) {
    // Agregamos los extremos de la tabla a la lista de cortes
    cuts.insert(cuts.begin(), 0); 
    cuts.push_back(L);
    int n = cuts.size();

    // Creamos una matriz para almacenar los costos mínimos
    Matriz<EntInf> dp(n,n,Infinito);

    // Caso base: no hay cortes entre dos puntos consecutivos
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1] = 0;
    }

    // Llenamos la matriz de manera bottom-up
    for (int length = 2; length < n; ++length) {                      //desde 2 porque ya hemos calculado los de longitud 1
        for (int i = 0; i < n - length; ++i) {                       // hasta n-length porque ya hemos calculado los de longitud length
            int j = i + length;                                     // j es el final del intervalo ya que length es la longitud del intervalo
            // Encontramos el mejor punto para realizar el corte entre i y j
            for (int k = i + 1; k < j; ++k) {                      // k es el punto de corte
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + 2*(cuts[j] - cuts[i]));
            }
        }
    }

    return dp[0][n - 1];
}

bool resuelveCaso() {
    int L, N;
    cin >> L >> N;

    if (L == 0 && N == 0) {
        return false;
    }
    vector<int> cuts(N);
    for (int i = 0; i < N; ++i) {
        cin >> cuts[i];
    }
    cout << minimo_esfuerzo(L, cuts) << endl;
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
