#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"

using namespace std;
using lli = long long int;

// Funcion recursiva para encontrar la combinación optima de cuerdas
vector<int> calcularDardos(const vector<int>& puntuaciones, int valor) {
    
    int n = puntuaciones.size();
    Matriz<lli> dardos(n+1, valor + 1, INT_MAX);

    // Caso base: para alcanzar un valor de 0, no se necesitan dardos
    for (int i = 0; i <= n; ++i) {
        dardos[i][0] = 0;
    }

    // Calar el menor numero de dardos para alcanzar cada valor de la diana
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= valor; ++j) {
            if (puntuaciones[i - 1] <= j) { // Si la puntuación es menor o igual que el valor
                dardos[i][j] = min(dardos[i - 1][j], dardos[i][j - puntuaciones[i - 1]] + 1);
            }
            else {
                dardos[i][j] = dardos[i - 1][j]; // No tomamos la puntuación
            }
        }
    }

    vector<int> sol;
    int j = valor;
    int i = n;

    while (j > 0) {
        if (puntuaciones[i - 1] <= j && dardos[i][j] != dardos[i - 1][j]) { // dardos[i][j] != dardos[i - 1][j] es que hemos cogido la puntuacion
            sol.push_back(puntuaciones[i - 1]);
            j = j - puntuaciones[i - 1];
        }
        else {
            // No tomamos mas puntuaciones del tipo i
            --i;
        }

        if (i == 0 && dardos[i][j] == INT_MAX) {
            return sol; // Devolver vector vacio
        }
    }

    return sol;
}

bool resuelveCaso() {

    int valor, sectores;
    cin >> valor >> sectores;

    if (!cin)return false;

    vector<int> puntuaciones(sectores);
    for (int i = 0; i < sectores; ++i) {
        cin >> puntuaciones[i];
    }

    // Calculamos la cantidad mínima de dardos necesarios
    vector<int> sol = calcularDardos(puntuaciones, valor);

    // Si no es posible alcanzar el valor, imprimimos "Imposible"
    if (sol.empty()) {
        cout << "Imposible" << endl;
    }
    else {
        // Imprimimos el resultado
        cout << sol.size() << ":";
        for (int i = 0; i < sol.size(); ++i) {
            cout << " " << sol[i];
        }
        cout << endl;
    }
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    /*
    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
    {
        resuelveCaso(); std::cin.ignore();
    }
    */
    while (resuelveCaso()) {

    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system(" PAUSE ");
#endif
    return 0;

}
