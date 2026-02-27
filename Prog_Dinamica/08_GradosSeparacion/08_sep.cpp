#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <unordered_map>


using namespace std;
using lli = long long int;

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<EntInf>& A) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<EntInf>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != Infinito)
                A[i][j] = i;
        }
    }
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (i == j && C[i][j] != 0) {
                    C[i][j] = 0;
                }
                else if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                    A[i][j] = A[k][j]; // actualizamos el camino
                }
            }
        }
    }
}

bool resuelveCaso() {
    int P, R;
    cin >> P >> R;

    if (!cin) return false;

    unordered_map<string, int> indice;
    Matriz<EntInf> G(P, P, Infinito); // Matriz de adyacencia inicializada con Infinito
    string persona1, persona2;

    for (int i = 0; i < R; ++i) {
        cin >> persona1 >> persona2;
        if (indice.find(persona1) == indice.end()) {
            int index = indice.size();
            indice[persona1] = index;
        }
        if (indice.find(persona2) == indice.end()) {
            int index = indice.size();
            indice[persona2] = index;
        }
        G[indice[persona1]][indice[persona2]] = 1;
        G[indice[persona2]][indice[persona1]] = 1;
    }

    Matriz<EntInf> C;     // Matriz para almacenar las distancias más cortas
    Matriz<EntInf> A;    // Matriz para reconstruir los caminos más cortos

    Floyd(G, C, A);

    // Encontrar el grado de separación máximo
    EntInf maxGrado = -1;
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < P; ++j) {
            if (C[i][j] == Infinito) {
                cout << "DESCONECTADA" << "\n";
                maxGrado = -2; // Se marca como -2 si la red está desconectada
                break;
            }
            maxGrado = max(maxGrado, C[i][j]);
        }
        if (maxGrado == -2) break;
    }
    EntInf cero = 0;
    if ( cero <= maxGrado ) {
        cout << maxGrado << "\n";
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
