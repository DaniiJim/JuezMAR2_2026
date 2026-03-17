#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"


using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
struct Cuerda {
    int longitud;
    int coste;
};
struct Solucion {
    EntInf sol;
};


Solucion resolverMatematicoAscendiente(const vector<Cuerda>& cuerdas, int N, int C) {
    Matriz<EntInf> m(N + 1, C + 1, 0);
    m[0][0] = 1;
    for (int i = 1; i <= N; i++)
    {
        m[i][0] = 1;
        for (int j = 1; j <= C; j++)
        {
            int L = cuerdas[i - 1].longitud;
            if (L > j) {
                m[i][j] = m[i - 1][j];
            }
            else {
                m[i][j] = m[i - 1][j] + m[i - 1][j - L];
            }
        }

    }
    return {m[N][C]};
}
Solucion resolverIngenieroAscendiente(const vector<Cuerda>& cuerdas, int N, int C) {
    Matriz<EntInf> m(N + 1, C + 1, Infinito);
    m[0][0] = 0;
    for (int i = 1; i <= N; i++)
    {
        m[i][0] = 0;
        for (int j = 1; j <= C; j++)
        {
            int L = cuerdas[i - 1].longitud;
            if (L > j) {
                m[i][j] = m[i - 1][j];
            }
            else {
                m[i][j] = min(m[i - 1][j], m[i - 1][j - L] + 1);
            }
        }

    }
    return {m[N][C]};
}
Solucion resolverEconomistaAscendiente(const vector<Cuerda>& cuerdas, int N, int C) {
    Matriz<EntInf> m(N + 1, C + 1, Infinito);
    m[0][0] = 0;
    for (int i = 1; i <= N; i++)
    {
        m[i][0] = 0;
        for (int j = 1; j <= C; j++)
        {
            int L = cuerdas[i - 1].longitud;
            int coste = cuerdas[i - 1].coste;
            
            if (L > j) {
                m[i][j] = m[i - 1][j];
            }
            else {
                m[i][j] = min(m[i - 1][j], m[i - 1][j - L] + coste);
            }
        }

    }
    return {m[N][C]};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C;
    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<Cuerda> cuerdas(N);
    for (int i = 0; i < N; i++)
    {
        Cuerda auxiliar;
        cin >> auxiliar.longitud >> auxiliar.coste;
        cuerdas[i] = auxiliar;
    }
    
    Solucion solMatematico = resolverMatematicoAscendiente(cuerdas, N, C);
    if(solMatematico.sol != 0){
        cout << "SI ";
        solMatematico.sol.print();
        cout << " ";
        Solucion solIngeniero = resolverIngenieroAscendiente(cuerdas, N, C);
        if(solIngeniero.sol != Infinito)
            solIngeniero.sol.print(); cout << " ";

        Solucion solEconomista = resolverEconomistaAscendiente(cuerdas, N, C);
        if(solEconomista.sol != Infinito)
            solEconomista.sol.print(); cout << "\n";          
    }
    else{
        cout << "NO\n";
    }

    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
//    std::ifstream in("casos.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//    system("PAUSE");
//#endif
    return 0;
}
