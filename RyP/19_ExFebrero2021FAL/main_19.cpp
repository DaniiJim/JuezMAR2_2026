#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include "Matriz.h"

using namespace std;

struct tDatos {
    int n, m; // plazas, comensales
    Matriz<double> dist;
    Matriz<bool> allegados;
};

struct Nodo {
    int k; // comensal que estamos sentando
    vector<int> asignados; // asignados[comensal] = plaza
    vector<bool> usada;    // usada[plaza] = true si está ocupada
    int parejas;           // número de parejas allegadas cercanas
    int estimacion_precio;

    bool operator<(const Nodo& otro) const {
        return estimacion_precio < otro.estimacion_precio; // queremos máximo
    }
};

int estimacionOptimista(const Nodo& nodo, const tDatos& d) {
    int posibles = nodo.parejas;
    for (int i = 0; i < nodo.k; ++i) {
        int pi = nodo.asignados[i];
        for (int j = nodo.k; j < d.m; ++j) {
            for (int pj = 0; pj < d.n; ++pj) {
                if (!nodo.usada[pj] &&
                    d.allegados[i][j] &&
                    d.dist[pi][pj] < 2.0) {
                    posibles++;
                    break;
                }
            }
        }
    }
    return posibles;
}

void resolver(const tDatos& d) {
    priority_queue<Nodo> cola;
    Nodo raiz;
    raiz.k = 0;
    raiz.asignados = vector<int>(d.m, -1);
    raiz.usada = vector<bool>(d.n, false);
    raiz.parejas = 0;
    raiz.estimacion_precio = 0;

    cola.push(raiz);
    int maxParejas = -1;

    while (!cola.empty() && cola.top().estimacion_precio > maxParejas) {
        Nodo actual = cola.top(); cola.pop();

        if (actual.k == d.m) {
            maxParejas = max(maxParejas, actual.parejas);
        } else {
            for (int p = 0; p < d.n; ++p) {
                if (!actual.usada[p]) {
                    bool ok = true;
                    for (int i = 0; i < actual.k && ok; ++i) {
                        int pi = actual.asignados[i];
                        if (!d.allegados[i][actual.k] && d.dist[pi][p] < 2.0)
                            ok = false;
                    }
                    if (ok) {
                        Nodo hijo = actual;
                        hijo.asignados[hijo.k] = p;
                        hijo.usada[p] = true;
                        hijo.k++;
                        for (int i = 0; i < hijo.k; ++i) {
                            if (d.allegados[i][hijo.k - 1] &&
                                d.dist[hijo.asignados[i]][p] < 2.0)
                                hijo.parejas++;
                        }
                        hijo.estimacion_precio = estimacionOptimista(hijo, d);
                        if (hijo.estimacion_precio > maxParejas)
                            cola.push(hijo);
                    }
                }
            }
        }
    }

    if (maxParejas == -1)
        cout << "CANCELA\n";
    else
        cout << "PAREJAS " << maxParejas << "\n";
}

bool resuelveCaso() {
    tDatos d;
    cin >> d.n >> d.m;
    if (!cin) return false;

    d.dist = Matriz<double>(d.n, d.n);
    for (int i = 0; i < d.n; ++i)
        for (int j = 0; j < d.n; ++j)
            cin >> d.dist[i][j];

    d.allegados = Matriz<bool>(d.m, d.m);
    for (int i = 0; i < d.m; ++i)
        for (int j = 0; j < d.m; ++j) {
            int x; cin >> x;
            d.allegados[i][j] = (x == 1);
        }

    resolver(d);
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
