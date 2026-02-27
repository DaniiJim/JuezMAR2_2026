#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <climits>
#include "Matriz.h"

using namespace std;


// 1. Nombre del problema
// Asignacion de productos a supermercados minimizando coste con restriccion de 3 productos por supermercado.

// 2. Representacion de las soluciones
// Una solucion se representa como una tupla de decisiones (x1, x2, ..., xn)
// donde xi es el supermercado en el que se compra el producto i.

// 3. Arbol de exploracion
// Cada nodo representa una solucion parcial con los k primeros productos asignados.
// Los nodos vivos se gestionan con una priority_queue, donde se expande el nodo con menor estimacion del coste total.

// 4. Funcion de estimacion
// La estimacion (coste + suma de minimos posibles) es una cota inferior del coste total:
// Se suma el coste actual con el precio minimo posible para cada producto restante,
// considerando solo los supermercados que no hayan alcanzado su limite de 3 productos.

// 5. Criterios de poda
// - Se poda si un supermercado supera los 3 productos asignados (no factible).
// - Se poda si la estimacion ya supera el mejor coste encontrado.

// 6. Llamada inicial y expansion
// Desde la raiz (sin productos asignados), se generan los hijos asignando el siguiente producto
// a cualquier supermercado que no haya alcanzado su limite. Cada hijo incrementa el nivel k
// y actualiza coste, asignacion y estimacion.

// 7. Coste
// Coste temporal: Exponencial en el peor caso, pero reducido por poda efectiva.
// Coste espacial: Depende del tamano de la priority_queue y del numero de nodos generados.




struct Nodo {
    int k; // producto que estamos asignando
    int coste;
    int coste_estimado;
    vector<int> asignacion; // asignacion[producto] = supermercado
    vector<int> cuenta_super; // cuenta_super[i] = cuantos productos lleva supermercado i

    bool operator<(const Nodo& otro) const {
        return coste_estimado > otro.coste_estimado; // menor estimacion es mejor (minimizar)
    }
};


// Esta función de estimación es OPTIMISTA, porque subestima el coste real que puede alcanzar el nodo. Es decir, calcula una cota inferior al coste total posible
int estimacionOptimista(const Nodo& nodo, const Matriz<int>& precios) {
    int est = nodo.coste;
    int n = precios.numcols();
    int m = precios.numfils();
    for (int i = nodo.k; i < n; ++i) {
        int minimo = INT_MAX;
        for (int j = 0; j < m; ++j) {
            if (nodo.cuenta_super[j] < 3) // solo si se puede aún comprar en ese super
                minimo = min(minimo, precios[j][i]);
        }
        est += minimo;
    }
    return est;
}


void resolver(const Matriz<int>& precios, int m, int n) {
    priority_queue<Nodo> pq;
    Nodo raiz;
    raiz.k = 0;
    raiz.coste = 0;
    raiz.asignacion = vector<int>(n, -1);
    raiz.cuenta_super = vector<int>(m, 0);
    raiz.coste_estimado = estimacionOptimista(raiz, precios);

    pq.push(raiz);
    int mejorCoste = INT_MAX;

    while (!pq.empty() && pq.top().coste_estimado < mejorCoste) {
        Nodo actual = pq.top(); pq.pop();

        if (actual.k == n) {
            mejorCoste = actual.coste;
        } else {
            for (int s = 0; s < m; ++s) {
                if (actual.cuenta_super[s] < 3) {
                    Nodo hijo = actual;
                    hijo.k++;
                    hijo.asignacion[hijo.k - 1] = s;
                    hijo.cuenta_super[s]++;
                    hijo.coste += precios[s][actual.k];
                    hijo.coste_estimado = estimacionOptimista(hijo, precios);

                    if (hijo.coste_estimado < mejorCoste) {
                        pq.push(hijo);
                    }
                }
            }
        }
    }

    if (mejorCoste == INT_MAX)
        cout << "Sin solucion factible\n";
    else
        cout << mejorCoste << "\n";
}



bool resuelveCaso() {
    int m, n;
    cin >> m >> n;
    if (!cin) return false;

    Matriz<int> precios(m, n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> precios[i][j];

    resolver(precios, m, n);

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
    system("PAUSE");
#endif
    return 0;
}