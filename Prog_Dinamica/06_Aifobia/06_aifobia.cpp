#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;
using lli = long long int;

void reconstruir (const string & palabra, const Matriz<EntInf> & dp, int i, int j,string & res) {
    if (i > j) return;
    if (i == j) {
        res.push_back(palabra[i]);
    }
    else if (palabra[i] == palabra[j]) {
        res.push_back(palabra[i]);
        reconstruir(palabra, dp, i + 1, j-1, res);   
        res.push_back(palabra[i]);
    }
    else if (dp[i + 1][j] < dp[i][j - 1]) {
        res.push_back(palabra[i]);
        reconstruir(palabra, dp, i + 1, j, res);
        res.push_back(palabra[i]);
        
    }
    else {
        res.push_back(palabra[j]);
        reconstruir(palabra, dp, i, j-1, res);
        res.push_back(palabra[j]);

    }
}

// Función para calcular el mínimo número de letras que faltan para convertir la palabra en un palíndromo
pair<EntInf, string> convertirPalindromo(string palabra) {
    int n = palabra.size();
    Matriz<EntInf> dp(n, n, 0);

    // Llenar la matriz dp usando programación dinámica
    for (int len = 2; len <= n; ++len) {                         // Longitud de la subcadena
        for (int i = 0; i <= n - len; ++i) {                    // Inicio de la subcadena
            int j = i + len - 1;                               // Fin de la subcadena
            if (palabra[i] == palabra[j]) {                   // Si los extremos de la subcadena son iguales
                dp[i][j] = dp[i + 1][j - 1];                 // No se necesitan letras adicionales
            }
            else {
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1; // Se necesita una letra adicional
            }
        }
    }
    string res;
    int j =n-1;
    reconstruir(palabra, dp, 0,j, res);

    // Calculamos el número de letras faltantes
    EntInf letrasFaltantes = dp[0][n - 1];
    return { letrasFaltantes, res };
}

bool resuelveCaso() {
    string palabra;
    cin >> palabra;

    if (!cin)return false;

    pair<EntInf, string> result = convertirPalindromo(palabra);
    cout << result.first << " " << result.second << endl;
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
