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

//Casos base
// minCoins(coins, quantities, 0) = 0
// minCoins(coins, quantities, j) = Infinito si no hay monedas que sumen j

// Casos recursivos
// minCoins(coins, quantities, j) = min(minCoins(coins, quantities, j - k * coins[i]) + k, minCoins(coins, quantities, j)) para k = 1, ..., quantities[i] y i = 0, ..., n - 1 




EntInf minCoins(vector<int>& coins, vector<int>& quantities, int target) {
    int n = coins.size();
    vector<EntInf> dp(target + 1, Infinito);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {                                                 //recorremos las monedas 
        for (int j = target; j >= 0; --j) {                                      //recorremos el target de mayor a menor por si hay que usar la misma moneda varias veces                    
            for (int k = 1; k <= quantities[i] && k * coins[i] <= j; ++k) {     //recorremos las cantidades de monedas que tenemos, 0  no se usa porque ya lo hemos inicializado
                if (dp[j - k * coins[i]] != Infinito) {                        //dp[j - k * coins[i]] es el valor que necesitamos para llegar a j con k monedas de valor coins[i]
                    dp[j] = min(dp[j], dp[j - k * coins[i]] + k);             // con +k sumamos las monedas que estamos usando
                }
            }
        }
    }

    return dp[target];
}


bool resuelveCaso() {
    int n;
    cin >> n;
    
    if(!cin) return false;

    vector<int> valores(n);
    vector<int> cantidad(n);

    for (int i = 0; i < n; ++i) {
        cin >> valores[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> cantidad[i];
    }

    int precio;
    cin >> precio;

    int totalCoins = 0;
    for (int i = 0; i < n; ++i) {
        totalCoins += cantidad[i] * valores[i];
    }

    if (totalCoins < precio) {
        cout << "NO" << endl;
    }
    else {
        EntInf minNeeded = minCoins(valores, cantidad, precio);
        if (minNeeded != Infinito) {
            cout << "SI " << minNeeded << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
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
