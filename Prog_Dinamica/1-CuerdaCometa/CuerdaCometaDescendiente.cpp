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


EntInf resolverMatematicoDescendiente(const vector<Cuerda>& cuerdas, int i, int j, Matriz<EntInf>& m) {
    if(j == 0)
        return 1;
    if (i == 0)
        return 0;
    else if (m[i][j] != -1)
        return  {m[i][j]};
    int L = cuerdas[i-1].longitud;
    if (L > j) 
        m[i][j] = resolverMatematicoDescendiente(cuerdas, i-1, j, m);
    else 
        m[i][j] = resolverMatematicoDescendiente(cuerdas, i-1, j, m) + resolverMatematicoDescendiente(cuerdas, i-1, j-L, m);
    
    return  {m[i][j]};
}
EntInf resolverIngenieroDescendiente(const vector<Cuerda>& cuerdas, int i, int j, Matriz<EntInf>& m) {
    if(j == 0)
        return 0;
    if (i == 0)
        return Infinito;
    else if (m[i][j] != -1)
        return {m[i][j]};
    int L = cuerdas[i-1].longitud;
    if (L > j) 
        m[i][j] = resolverIngenieroDescendiente(cuerdas, i-1, j, m);
    else {
        EntInf no_poner = resolverIngenieroDescendiente(cuerdas, i-1, j, m);
        EntInf poner = resolverIngenieroDescendiente(cuerdas, i-1, j-L, m) + 1;
        
        m[i][j] = min(no_poner, poner);
    }
    
    return  {m[i][j]};
}
EntInf resolverEconomistaDescendiente(const vector<Cuerda>& cuerdas, int i, int j, Matriz<EntInf>& m) {
    if(j == 0)
        return 0;
    if (i == 0)
        return Infinito;
    else if (m[i][j] != -1)
        return {m[i][j]};
    int L = cuerdas[i-1].longitud;
    int coste = cuerdas[i-1].coste;

    if (L > j) 
        m[i][j] = resolverEconomistaDescendiente(cuerdas, i-1, j, m);
    else {
        EntInf no_poner = resolverEconomistaDescendiente(cuerdas, i-1, j, m);
        EntInf poner = resolverEconomistaDescendiente(cuerdas, i-1, j-L, m) + coste;
        
        m[i][j] = min(no_poner, poner);
    }
    
    return {m[i][j]};
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
    Matriz<EntInf> mMat(N + 1, C + 1, -1);
    Matriz<EntInf> mIng(N + 1, C + 1, -1);
    Matriz<EntInf> mEcon(N + 1, C + 1, -1);
    
    EntInf solMatematico = resolverMatematicoDescendiente(cuerdas, N, C, mMat);
    if(solMatematico != 0){
        cout << "SI ";
        solMatematico.print();
        cout << " ";
        EntInf solIngeniero = resolverIngenieroDescendiente(cuerdas, N, C, mIng);
        if(solIngeniero != Infinito)
            solIngeniero.print(); cout << " ";

        EntInf solEconomista = resolverEconomistaDescendiente(cuerdas, N, C, mEcon);
        if(solEconomista != Infinito)
            solEconomista.print(); cout << "\n";          
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
