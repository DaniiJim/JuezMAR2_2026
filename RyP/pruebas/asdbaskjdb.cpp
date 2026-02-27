#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>
using namespace std;

struct tDatos {
    int n; // número de canciones
    int cara1, cara2; // duración máxima de cada cara
    vector<int> duracion;
    vector<int> puntuacion;
};

struct Nodo {
    int k; // canción actual
    int tiempo1, tiempo2; // tiempo ocupado en cada cara
    int puntuacionActual;
    int estimacion; // cota optimista
    vector<bool> usada; // canciones usadas

    bool operator<(const Nodo& otro) const {
        return estimacion < otro.estimacion; // menor estimación = más prometedor
    }
};

int estimacionOptimista(const Nodo& nodo, const tDatos& datos) {
    int est = nodo.puntuacionActual;
    // Añadir puntuaciones de canciones no usadas
    for (int i = nodo.k; i < datos.n; ++i) {
        if (!nodo.usada[i]) est += datos.puntuacion[i];
    }
    return est;
}

int resolver(const tDatos& datos) {
    Nodo raiz;
    raiz.k = 0;
    raiz.tiempo1 = 0;
    raiz.tiempo2 = 0;
    raiz.puntuacionActual = 0;
    raiz.usada.assign(datos.n, false);
    raiz.estimacion = estimacionOptimista(raiz, datos);

    priority_queue<Nodo> cola;
    cola.push(raiz);

    int mejor = 0;

    while (!cola.empty() && cola.top().estimacion > mejor) {
        Nodo actual = cola.top(); cola.pop();

        if (actual.k == datos.n) {
            mejor = max(mejor, actual.puntuacionActual);
        } else {
            // Opción 1: no usar canción k
            Nodo sinUsar = actual;
            sinUsar.k++;
            sinUsar.estimacion = estimacionOptimista(sinUsar, datos);
            if (sinUsar.estimacion > mejor)
                cola.push(sinUsar);

            // Opción 2: usar canción k en cara 1
            if (actual.tiempo1 + datos.duracion[actual.k] <= datos.cara1) {
                Nodo conCara1 = actual;
                conCara1.k++;
                conCara1.tiempo1 += datos.duracion[actual.k];
                conCara1.puntuacionActual += datos.puntuacion[actual.k];
                conCara1.usada[actual.k] = true;
                conCara1.estimacion = estimacionOptimista(conCara1, datos);
                if (conCara1.estimacion > mejor)
                    cola.push(conCara1);
            }

            // Opción 3: usar canción k en cara 2
            if (actual.tiempo2 + datos.duracion[actual.k] <= datos.cara2) {
                Nodo conCara2 = actual;
                conCara2.k++;
                conCara2.tiempo2 += datos.duracion[actual.k];
                conCara2.puntuacionActual += datos.puntuacion[actual.k];
                conCara2.usada[actual.k] = true;
                conCara2.estimacion = estimacionOptimista(conCara2, datos);
                if (conCara2.estimacion > mejor)
                    cola.push(conCara2);
            }
        }
    }
    return mejor;
}

bool resuelveCaso() {
    tDatos datos;
    cin >> datos.n;
    if (datos.n == 0) return false;
    cin >> datos.cara1;
    datos.cara2 = datos.cara1; // la cinta tiene dos caras de igual tamaño

    datos.duracion.resize(datos.n);
    datos.puntuacion.resize(datos.n);
    for (int i = 0; i < datos.n; ++i) {
        cin >> datos.duracion[i] >> datos.puntuacion[i];
    }

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