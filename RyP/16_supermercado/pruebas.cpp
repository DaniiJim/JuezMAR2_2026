#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include "Matriz.h"
using namespace std;

struct tDatos {
    int m, n;
    Matriz<int> precio; // precio[i][j]: precio del producto i en supermercado j
};

struct Nodo {
    int k;                    // índice de producto actual
    vector<int> sol;          // sol[i] = supermercado asignado al producto i
    vector<int> usados;       // usados[j] = número de productos comprados en supermercado j
    int costeActual;
    int cotaOpt;

    bool operator<(const Nodo& otro) const {
        return cotaOpt > otro.cotaOpt; // menor cotaOpt tiene mayor prioridad
    }
};

int calcOptimista(const Nodo& nodo, const tDatos& datos) {
    int cota = nodo.costeActual;
    for (int i = nodo.k; i < datos.n; ++i) {
        int menor = numeric_limits<int>::max();
        for (int j = 0; j < datos.m; ++j)
            menor = min(menor, datos.precio[i][j]);
        cota += menor;
    }
    return cota;
}

int calcPesimista(const Nodo& nodo, const tDatos& datos) {
    int coste = nodo.costeActual;
    vector<int> cap = nodo.usados;
    for (int i = nodo.k; i < datos.n; ++i) {
        int mejor = numeric_limits<int>::max();
        int mj = -1;
        for (int j = 0; j < datos.m; ++j) {
            if (cap[j] < 3 && datos.precio[i][j] < mejor) {
                mejor = datos.precio[i][j];
                mj = j;
            }
        }
        if (mj == -1) return numeric_limits<int>::max();
        cap[mj]++;
        coste += mejor;
    }
    return coste;
}

int resolver(const tDatos& datos) {
    Nodo raiz;
    raiz.k = 0;
    raiz.sol.assign(datos.n, -1);
    raiz.usados.assign(datos.m, 0);
    raiz.costeActual = 0;
    raiz.cotaOpt = calcOptimista(raiz, datos);

    priority_queue<Nodo> pq;
    pq.push(raiz);

    int mejor = calcPesimista(raiz, datos);

    while (!pq.empty() && pq.top().cotaOpt < mejor) {
        Nodo act = pq.top(); pq.pop();
        if (act.k == datos.n) {
            mejor = min(mejor, act.costeActual);
        } else {
            for (int j = 0; j < datos.m; ++j) {
                if (act.usados[j] < 3) {
                    Nodo sig = act;
                    sig.k = act.k + 1;
                    sig.sol[act.k] = j;
                    sig.usados[j]++;
                    sig.costeActual += datos.precio[act.k][j];
                    sig.cotaOpt = calcOptimista(sig, datos);
                    if (sig.cotaOpt < mejor) {
                        int pes = calcPesimista(sig, datos);
                        if (pes < mejor) mejor = pes;
                        pq.push(sig);
                    }
                }
            }
        }
    }
    return mejor;
}

bool resuelveCaso() {
    int m, n;
    cin >> m >> n;
    if (!cin) return false;
    tDatos datos;
    datos.m = m;
    datos.n = n;
    datos.precio = Matriz<int>(n, m);
    for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i)
            cin >> datos.precio[i][j];

    int mejor = resolver(datos);
    if (mejor == numeric_limits<int>::max())
        cout << "Sin solucion factible\n";
    else
        cout << mejor << "\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    int casos;
    cin >> casos;
    while (casos--) resuelveCaso();
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
