#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


// 1. Nombre del problema
// Seleccion de canciones para una cinta con dos caras maximizando la puntuacion total.

// 2. Representacion de las soluciones
// Una solucion se representa como una tupla (x1, x2, ..., xn) donde xi indica si la cancion i:
// - no se mete (0)
// - se graba en la cara A (1)
// - se graba en la cara B (2)

// 3. Arbol de exploracion
// Cada nodo representa una solucion parcial con las k primeras canciones ya evaluadas.
// Se usan tres ramas por nodo: no incluir la cancion, meterla en cara A o meterla en cara B.
// Los nodos se gestionan con una priority_queue que expande primero los de mayor estimacion (maximizacion).

// 4. Funcion de estimacion --> OPTIMISTA
// La estimacion es la puntuacion acumulada mas la suma de las puntuaciones de las canciones restantes
// que podrian caber en alguna de las dos caras. Esta cota superior nos permite descartar nodos
// que no podran superar la mejor solucion actual.

// 5. Criterios de poda
// Se poda si la estimacion de un nodo ya no mejora la mejor puntuacion encontrada hasta el momento.

// 6. Llamada inicial y expansion
// Se empieza con la raiz: sin canciones grabadas, puntuacion 0, caras vacias.
// En cada nodo se generan hasta tres hijos (una cancion sin usar): no grabarla, grabarla en cara A o en cara B si hay espacio.

// 7. Coste
// Coste temporal: Exponencial en el peor caso (3^n), pero reducido por poda efectiva.
// Coste espacial: Uso de priority_queue y estructuras auxiliares por cada nodo generado.


struct Cancion {
    int duracion;
    int puntuacion;
};

struct Nodo {
    int k;
    int caraA, caraB;
    int puntuacion;
    int coste_estimado;
    vector<bool> usada;

    bool operator<(const Nodo& otro) const {
        return coste_estimado < otro.coste_estimado;
    }
};


//Es uan funcion de estimacion optimista xq lo que hace es maximizar la puntuacion total, asume lo mejor posible en cada momento
int estimacionOptimista(const Nodo& nodo, const vector<Cancion>& canciones, int durA, int durB) {
    int n = canciones.size();
    int est = nodo.puntuacion;
    for (int i = nodo.k; i < n; ++i) {
        if (!nodo.usada[i]) {
            if (nodo.caraA + canciones[i].duracion <= durA || nodo.caraB + canciones[i].duracion <= durB) {
                est += canciones[i].puntuacion;
            }
        }
    }
    return est;
}

int resolver(const vector<Cancion>& canciones, int durA, int durB) {
    int N = canciones.size();
    int mejorPuntuacion = 0;
    priority_queue<Nodo> pq;

    Nodo raiz;
    raiz.k = 0;
    raiz.caraA = 0;
    raiz.caraB = 0;
    raiz.puntuacion = 0;
    raiz.usada = vector<bool>(N, false);
    raiz.coste_estimado = estimacionOptimista(raiz, canciones, durA, durB);

    pq.push(raiz);

    while (!pq.empty() && pq.top().coste_estimado > mejorPuntuacion) {
        Nodo actual = pq.top(); pq.pop();

        if (actual.k == N) {
            mejorPuntuacion = max(mejorPuntuacion, actual.puntuacion);
        } else {
            int i = actual.k;

            // Opcion 1: no meter la cancion
            Nodo hijo1 = actual;
            hijo1.k++;
            hijo1.coste_estimado = estimacionOptimista(hijo1, canciones, durA, durB);
            if (hijo1.coste_estimado > mejorPuntuacion)
                pq.push(hijo1);

            // Opcion 2: meter en cara A
            if (actual.caraA + canciones[i].duracion <= durA) {
                Nodo hijo2 = actual;
                hijo2.k++;
                hijo2.caraA += canciones[i].duracion;
                hijo2.puntuacion += canciones[i].puntuacion;
                hijo2.usada[i] = true;
                hijo2.coste_estimado = estimacionOptimista(hijo2, canciones, durA, durB);
                if (hijo2.coste_estimado > mejorPuntuacion)
                    pq.push(hijo2);
            }

            // Opcion 3: meter en cara B
            if (actual.caraB + canciones[i].duracion <= durB) {
                Nodo hijo3 = actual;
                hijo3.k++;
                hijo3.caraB += canciones[i].duracion;
                hijo3.puntuacion += canciones[i].puntuacion;
                hijo3.usada[i] = true;
                hijo3.coste_estimado = estimacionOptimista(hijo3, canciones, durA, durB);
                if (hijo3.coste_estimado > mejorPuntuacion)
                    pq.push(hijo3);
            }
        }
    }

    return mejorPuntuacion;
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    int durA, durB;
    cin >> durA;
    durB = durA;
    vector<Cancion> canciones(N);
    for (int i = 0; i < N; ++i) cin >> canciones[i].duracion >> canciones[i].puntuacion;

    int resultado = resolver(canciones, durA, durB);
    cout << resultado << "\n";

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