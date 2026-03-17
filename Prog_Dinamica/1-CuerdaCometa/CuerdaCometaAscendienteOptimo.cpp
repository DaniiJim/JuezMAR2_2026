#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"


using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
struct Cuerda {
    long long int longitud;
    long long int coste;
};
struct Solucion {
    EntInf sol;
};


Solucion resolverMatematicoAscendiente(const vector<Cuerda>& cuerdas, long long int N, long long int C) {
    //Matriz<EntInf> m(N + 1, C + 1, 0);
    vector<long long int> v(C + 1, 0);
    v[0] = 1;
    for (long long int i = 0; i < N; i++)
    {
        long long int L = cuerdas[i].longitud;
        for (long long int j = C; j >= L; j--)
        {
            v[j] += v[j-L];
        }

    }
    return {v[C]};
}
Solucion resolverIngenieroAscendiente(const vector<Cuerda>& cuerdas, long long int N, long long int C) {
    vector<EntInf> v(C + 1, Infinito);
    v[0] = 0;
    for (long long int i = 0; i < N; i++)
    {
        long long int L = cuerdas[i].longitud;
        for (long long int j = C; j >= L; j--)
        {
            v[j] = min(v[j], v[j-L] + 1);
        }

    }
    return {v[C]};
}
Solucion resolverEconomistaAscendiente(const vector<Cuerda>& cuerdas, long long int N, long long int C) {
    vector<EntInf> v(C + 1, Infinito);
    v[0] = 0;
    for (long long int i = 0; i < N; i++)
    {
        long long int L = cuerdas[i].longitud;
        long long int Coste = cuerdas[i].coste;
        for (long long int j = C; j >= L; j--)
        {
            v[j] = min(v[j], v[j-L] + Coste);
        }

    }
    return {v[C]};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    long long int N, C;
    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<Cuerda> cuerdas(N);
    for (long long int i = 0; i < N; i++)
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
        if(solIngeniero.sol != Infinito){
            solIngeniero.sol.print(); 
            cout << " ";
        }

        Solucion solEconomista = resolverEconomistaAscendiente(cuerdas, N, C);
        if(solEconomista.sol != Infinito){
            solEconomista.sol.print(); 
            cout << "\n";          
        }
    }
    else{
        cout << "NO\n";
    }

    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
    return 0;
}
