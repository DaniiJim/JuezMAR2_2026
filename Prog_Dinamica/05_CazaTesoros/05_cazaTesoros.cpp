#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include "Matriz.h"

using namespace std;
using lli = long long int;

struct Cofre {
    int profundidad;
    int oro;
};

// Función recursiva para calcular el costo mínimo
int maxOroRecuperado(int T, const vector<Cofre>& cofres, vector<vector<lli>>& dp) {
    int n = cofres.size();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= T; ++j) {
            int p = cofres[i - 1].profundidad;
            int oro = cofres[i - 1].oro;
            if (p * 3 <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p * 3] + oro);
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][T];
}

bool resuelveCaso() {
    int T, N;
    cin >> T >> N;

    if (!cin)return false;

    vector<Cofre> cofres(N);
    for (int i = 0; i < N; ++i) {
        cin >> cofres[i].profundidad >> cofres[i].oro;
    }

    vector<vector<lli>> dp(N + 1, vector<lli>(T + 1, 0));
    lli maxOro = maxOroRecuperado(T, cofres, dp);
    cout << maxOro << endl;

    // Imprimir cofres seleccionados
    vector<pair<int, int>> cofresSeleccionados;
    int i = N;
    int j = T;
    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i - 1][j]) {
            cofresSeleccionados.push_back({ cofres[i - 1].profundidad, cofres[i - 1].oro });
            j -= cofres[i - 1].profundidad * 3;
        }
        i--;
    }

    cout << cofresSeleccionados.size() << endl;
    for (int k = cofresSeleccionados.size() - 1; k >= 0; --k) {
        cout << cofresSeleccionados[k].first << " " << cofresSeleccionados[k].second << endl;
    }

    cout << "---" << endl;
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
