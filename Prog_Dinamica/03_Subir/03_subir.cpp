#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"

using namespace std;
using lli = long long int;

int calcularMaximo(const Matriz<lli>& tablero, Matriz<lli>& dp, int fila, int columna, int N) {
    // Si ya hemos calculado la respuesta para esta casilla, la devolvemos
    if (fila == 0) return dp[fila][columna];

    // Si ya hemos visitado esta casilla, devolvemos su valor almacenado en dp
    if (dp[fila][columna] != INT_MIN) return dp[fila][columna];

    // Movimientos posibles: arriba, arriba-izquierda, arriba-derecha
    int maximo = INT_MIN;
    for (int i = -1; i <= 1; ++i) {
        int nuevaFila = fila - 1;
        int nuevaColumna = columna + i;
        if (nuevaColumna >= 0 && nuevaColumna < N) {// Si la columna está dentro del tablero
            maximo = max(maximo, calcularMaximo(tablero, dp, nuevaFila, nuevaColumna, N));
        }
    }

    // Agregamos el valor de la casilla actual al máximo obtenido
    maximo += tablero[fila][columna];

    // Almacenamos el máximo calculado en dp
    return dp[fila][columna] = maximo;
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (!cin)return false;

    Matriz<lli> tablero(N, N, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> tablero[i][j];
        }
    }

    // Inicializamos la matriz de memorización con INT_MIN
    Matriz<lli> dp(N, N, INT_MIN);
    // Sumamos los valores de la primera fila al dp
    for (int j = 0; j < N; ++j) { 
        dp[0][j] = tablero[0][j];
    }

    // Calculamos la máxima cantidad que se puede obtener para cada casilla de la última fila
    int maximoGlobal = INT_MIN;
    int columnaMaxima = -1;
    for (int j = 0; j < N; ++j) {
        int maximo = calcularMaximo(tablero, dp, N - 1, j, N);
        if (maximo > maximoGlobal) {
            maximoGlobal = maximo;
            columnaMaxima = j + 1;
        }
    }

    // Imprimimos el resultado
    cout << maximoGlobal << " " << columnaMaxima << "\n";
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
