#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;
using ll = long long int;

ll minCombs(vector<pair<int, int>>& cords, int L) {

    vector<ll> combinations(L + 1, 0), comb_nuevo(L + 1);
    combinations[0] = 1;
  
    for (int i = 1; i <= cords.size(); ++i){
        for (int j = 0; j <= L; ++j) {
            if (j < cords[i - 1].first) { //si la longitud de la cuerda es mayor que la longitud de la cuerda actual que estamos mirando
                comb_nuevo[j] = combinations[j];
            }
            else
            {
                comb_nuevo[j] = combinations[j - cords[i - 1].first] + combinations[j];
            }
        }
        swap( comb_nuevo, combinations);
    }

    return combinations[L];
}

EntInf minCordsss ( vector<pair<int, int>>& cords, int L) {
    vector<EntInf> minCords(L + 1, Infinito), minCords_nuevo(L + 1);
    minCords[0] = 0;

    for (int i = 1; i <= cords.size(); ++i) {
            for (int j = 0; j <= L; ++j) {
                if(j < cords[i - 1].first) {
                    minCords_nuevo[j] = minCords[j];
                }
                else
                    minCords_nuevo[j] = min(minCords[j], minCords[j - cords[i - 1].first] + 1);  
            }swap(minCords_nuevo,minCords);
    }
    return minCords[L];
}

EntInf minCosttt ( vector<pair<int, int>>& cords, int L) {
    vector<EntInf> minCost(L + 1, Infinito), minCost_nuevo(L + 1);
    minCost[0] = 0;

    for (int i = 1; i <= cords.size(); ++i) {
        for (int j = 0; j <= L; ++j) {
            if (j < cords[i - 1].first) {
                minCost_nuevo[j] = minCost[j];
            }
            else
                minCost_nuevo[j] = min(minCost[j], minCost[j - cords[i - 1].first] + cords[i - 1].second);
        }swap(minCost_nuevo,minCost);
    }
    return minCost[L];
}


bool resuelveCaso() {

    int n, L;
    cin >> n >> L;
    if (!cin) return false;

    vector<pair<int, int>> cords(n); // longitud, coste
    for (int i = 0; i < n; ++i) {
        cin >> cords[i].first >> cords[i].second;
    }

    // Inicializamos las matrices
    vector<EntInf> minCords(L + 1, Infinito);
    vector<EntInf> minCost(L + 1, Infinito);

    ll ways = minCombs(cords, L);
    EntInf minCords_ = 0;
    EntInf minCost_ = 0;

    if(ways != 0)
         minCords_ = minCordsss(cords, L);
         minCost_ = minCosttt(cords, L);


    if (ways != 0) {
        cout << "SI " << ways << " " << minCords_ << " " << minCost_ << "\n";
    }
    else {
        cout << "NO" << "\n";
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