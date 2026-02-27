#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include "Matriz.h"
using namespace std;

struct tDatos {
    int n;
    Matriz<int> tiempos; // tiempos[i][j] = funcionario i tarda esto en trabajo j
};

struct Nodo {
    int k; // funcionario actual
    vector<int> asignacion; // asignacion[i] = trabajo asignado al funcionario i
    vector<bool> libre; // trabajos disponibles
    int tiempoActual;
    int cotaOptimista;

    bool operator<(const Nodo& otro) const {
        return cotaOptimista > otro.cotaOptimista; // menor cota = más prometedor
    }
};

int calcOptimista(const Nodo& nodo, const tDatos& datos) {
    int suma = nodo.tiempoActual;
    for (int i = nodo.k; i < datos.n; ++i) {
        int mejor = numeric_limits<int>::max();
        for (int j = 0; j < datos.n; ++j) {
            if (nodo.libre[j]) mejor = min(mejor, datos.tiempos[i][j]);
        }
        suma += mejor;
    }
    return suma;
}

int calcPesimista(const Nodo& nodo, const tDatos& datos) {
    int suma = nodo.tiempoActual;
    vector<bool> libres = nodo.libre;
    for (int i = nodo.k; i < datos.n; ++i) {
        int mejor = numeric_limits<int>::max();
        int bestJ = -1;
        for (int j = 0; j < datos.n; ++j) {
            if (libres[j] && datos.tiempos[i][j] < mejor) {
                mejor = datos.tiempos[i][j];
                bestJ = j;
            }
        }
        if (bestJ != -1) {
            libres[bestJ] = false;
            suma += mejor;
        }
    }
    return suma;
}

int resolver(const tDatos& datos) {
    Nodo raiz;
    raiz.k = 0;
    raiz.asignacion.assign(datos.n, -1);
    raiz.libre.assign(datos.n, true);
    raiz.tiempoActual = 0;
    raiz.cotaOptimista = calcOptimista(raiz, datos);

    priority_queue<Nodo> cola;
    cola.push(raiz);

    int mejor = calcPesimista(raiz, datos);

    while (!cola.empty() && cola.top().cotaOptimista < mejor) {
        Nodo actual = cola.top(); cola.pop();

        if (actual.k == datos.n) {
            mejor = min(mejor, actual.tiempoActual);
        } else {
            for (int j = 0; j < datos.n; ++j) {
                if (actual.libre[j]) {
                    Nodo hijo = actual;
                    hijo.k++;
                    hijo.asignacion[actual.k] = j;
                    hijo.libre[j] = false;
                    hijo.tiempoActual += datos.tiempos[actual.k][j];
                    hijo.cotaOptimista = calcOptimista(hijo, datos);
                    if (hijo.cotaOptimista < mejor) {
                        int pes = calcPesimista(hijo, datos);
                        if (pes < mejor) mejor = pes;
                        cola.push(hijo);
                    }
                }
            }
        }
    }
    return mejor;
}

bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;

    tDatos datos;
    datos.n = n;
    datos.tiempos = Matriz<int>(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> datos.tiempos[i][j];

    cout << resolver(datos) << '\n';
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}