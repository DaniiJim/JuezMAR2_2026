#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;
using lli = long long int;

void reconstruir(const Matriz<EntInf>& dp, const string& palabra1, const string& palabra2, int i, int j, string& res) {
    if (i == 0 || j == 0) {
        return;
    }
    if (palabra1[i - 1] == palabra2[j - 1]) {
        reconstruir( dp, palabra1, palabra2, i - 1, j - 1, res);
        res.push_back(palabra1[i - 1]);
    }
    else if (dp[i - 1][j] > dp[i][j - 1]) { 
        reconstruir(dp, palabra1, palabra2, i - 1, j, res);
    }
    else {
        reconstruir(dp, palabra1, palabra2, i, j - 1, res);
    }
}

// Función para calcular el mínimo número de letras que faltan para convertir la palabra en un palíndromo
string convertirPalindromo(string palabra1,string palabra2) {
    int n = palabra1.size();
    int m = palabra2.size();
    Matriz<EntInf> dp(n + 1, m + 1, 0);

    // Llenar la matriz dp utilizando programación dinámica
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (palabra1[i - 1] == palabra2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string res;
    reconstruir(dp, palabra1, palabra2, n, m, res);
    return res;
}

bool resuelveCaso() {
    string palabra1,palabra2;
    cin >> palabra1 >> palabra2;

    if (!cin)return false;

    string result = convertirPalindromo(palabra1, palabra2);
    cout << result << "\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    //int numCasos;
    //cin >> numCasos;
    //for (int i = 0; i < numCasos; ++i)
    //{
    //    resuelveCaso(); std::cin.ignore();
    //}

    while (resuelveCaso()) {

    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system(" PAUSE ");
#endif
    return 0;
}
