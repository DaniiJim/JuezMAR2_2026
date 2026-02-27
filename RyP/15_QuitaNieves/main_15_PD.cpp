#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Matriz.h"

using namespace std;


/*
Asignacion de carros quitanieves a caminos maximizando la calidad total de limpieza

2 Representacion de las soluciones
    Una solucion se representa como una tupla (x0, x1, ..., xn-1), donde xi es el camino al que se asigna el carro i
    Cada carro se asigna a lo sumo a un camino y cada camino a lo sumo a un carro
    La solucion final es un vector de los carros a caminos compatibles

3 Estructura del subproblema
    En cada llamada recursiva se intenta asignar el carro i a un camino libre compatible
    Se usa un vector de marcas para indicar que caminos ya han sido usados
    El estado se codifica como un entero para indexar la tabla de memoizacion

4 Subproblemas repetidos
    Para evitar resolver el mismo caso varias veces se utiliza una tabla de memoizacion
    Se guarda el mejor resultado posible desde el carro i con una combinacion concreta de caminos ya asignados

5 Llamada inicial y expansion
    La llamada inicial comienza en el carro 0 con todos los caminos libres (vector de marcas a false)
    En cada llamada recursiva se prueba asignar el carro actual a cada camino compatible disponible

6 Coste
    Coste temporal O(n * 2^m) siendo n el numero de carros y m el numero de caminos
    Coste espacial O(n * 2^m) por la tabla de memoizacion que guarda los estados visitados
*/




int resolver(int i, vector<bool>& marcas_caminos, vector<int>& anchura_carros, vector<int>& anchura_caminos, Matriz<int>& calidades, Matriz<int>& memo) {
    if (i == anchura_carros.size()) return 0;

    // Se convierte el vector de marcas a un entero
    int codificado = 0;
    for (int j = 0; j < marcas_caminos.size(); ++j) {
        if (marcas_caminos[j]) codificado |= (1 << j);
    }

    if (memo[i][codificado] != -1) return memo[i][codificado];

    int mejor = 0;
    for (int j = 0; j < calidades.numcols(); j++) {
        if (!marcas_caminos[j] && anchura_carros[i] <= anchura_caminos[j]) {
            marcas_caminos[j] = true;
            mejor = max(mejor, calidades[i][j] + resolver(i + 1, marcas_caminos,anchura_carros, anchura_caminos, calidades, memo));
            marcas_caminos[j] = false;
        }
    }

    return memo[i][codificado] = mejor;
}


void resuelveCaso() {

    // n carros, m caminos, n < m
    // Cada carro solo puede ir a caminos con anchura mayor o igual
    // Cada carro se asigna a un solo camino, y viceversa

    int n, m;
    cin >> n >> m;

    vector<int> anchura_carros(n), anchura_caminos(m);

    for (int i = 0; i < n; i++) cin >> anchura_carros[i];
    for (int i = 0; i < m; i++) cin >> anchura_caminos[i];

    Matriz<int> calidades = Matriz<int>(n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> calidades[i][j];

    
    // memo[i][j] = mejor calidad asignando desde el carro i con caminos usados j
    Matriz<int> mejor_calidad(n + 1, 1 << m, -1);   // 1 << m = 1^m
    vector<bool> caminos_usados(m, false);
    int resultado = resolver(0, caminos_usados, anchura_carros, anchura_caminos, calidades, mejor_calidad);
    cout << resultado << "\n";
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    
    unsigned int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
    

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
