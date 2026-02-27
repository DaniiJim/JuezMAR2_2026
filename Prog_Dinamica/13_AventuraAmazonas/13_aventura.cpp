#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
#include "EnterosInf.h"
#include <sstream>
#include <unordered_map>


using namespace std;
using lli = long long int;


bool resuelveCaso() {
    string cadena;
    cin >> cadena;
    if (!cin)return false;

    if (true ){
        cout << "SI" << "\n";
    }
    else {
        cout << "NO" << "\n";
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
