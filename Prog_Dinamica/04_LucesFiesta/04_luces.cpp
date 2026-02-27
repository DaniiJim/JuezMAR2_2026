#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;
using lli = long long int;

// Estructura para representar cada tipo de bombilla
struct Bombilla {
    int potencia;
    int coste;
};

// Función recursiva para calcular el costo mínimo
void calcularCostoPotenciaMinimavectores(vector<Bombilla>const& bombillas, lli PMax, lli PMin, lli N, vector<EntInf>& memo) {

    for (lli i = 1; i <= N; ++i) {
        for (lli potencia = 0; potencia <= PMax; ++potencia) {
            if (potencia - bombillas[i - 1].potencia < 0) {
                memo[potencia] = memo[potencia];
            }
            else
                memo[potencia] = min(memo[potencia], memo[potencia - bombillas[i - 1].potencia] + bombillas[i - 1].coste);
        }
    }

}



bool resuelveCaso() {
    int N, PMax, PMin;
    cin >> N >> PMax >> PMin;

    if (!cin)return false;

    vector<Bombilla> bombillas(N);
    for (int i = 0; i < N; ++i) {
        cin >> bombillas[i].potencia;
    }

    for (int i = 0; i < N; ++i) {
        cin >> bombillas[i].coste;
    }


    vector<EntInf> memo(PMax + 1, Infinito);
    memo[0] = 0;
    // Llamar a la función recursiva
    calcularCostoPotenciaMinimavectores(bombillas, PMax, PMin, N, memo);

    EntInf costoMinimo = Infinito;
    lli potenciaRequerida = -1;
    for (lli potencia = PMin; potencia <= PMax; ++potencia) {
        if (memo[potencia] < costoMinimo) {
            potenciaRequerida = potencia;
            costoMinimo = memo[potencia];
        }
    }

    // Imprimir el resultado
    if (costoMinimo == Infinito) {
        cout << "IMPOSIBLE\n";
    }
    else {
        cout << costoMinimo << " " << potenciaRequerida << "\n";
    }
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
