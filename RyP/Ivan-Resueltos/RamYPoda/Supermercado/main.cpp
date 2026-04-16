#include <iostream>
#include <vector>
#include <queue>
#include "Matriz.h"
using namespace std;


struct Nodo{
    int k;
    int coste_estimado;
    int coste;
    vector<int> supers_usados;

    bool operator<(const Nodo& otro) const {
        return otro.coste_estimado < coste_estimado;
    }


};

int calcular_min_columna(const Matriz<int>& productos_super, const int& k){
    int minimo = productos_super[0][k];

    for (int i = 0; i < productos_super.numfils(); i++)
    {
        minimo = min(minimo, productos_super[i][k]);
    }
    
    return minimo;
}

int calcular_minimo_desdek(const vector<int>& suma_minima_acc, const int& k, const int& coste){
    if (k < 0) {
        return suma_minima_acc[0] + coste;
    }

    if (k >= static_cast<int>(suma_minima_acc.size())) {
        return coste;
    }

    return suma_minima_acc[k] + coste;
}

int asignar(const Matriz<int>& productos_super, const vector<int>& suma_minima_acc){
    int num_supers = productos_super.numfils();
    int num_products = productos_super.numcols();
    priority_queue<Nodo> pq;
    Nodo Y;
    Y.k = -1;
    Y.coste = 0;
    Y.coste_estimado = calcular_minimo_desdek(suma_minima_acc, 0, Y.coste);
    Y.supers_usados = vector<int>(num_supers, 0);
    int mejor_coste = INT32_MAX;        // Aquí podríamos meter una cota pesimista = una solución voraz que escoja el mínimo siempre y cuando mantenga la restricción
    pq.push(Y);

    while(!pq.empty() && pq.top().coste_estimado < mejor_coste){
        Y = pq.top();
        pq.pop();

        for (int i = 0; i < num_supers; i++)
        {
            if(Y.supers_usados[i] < 3){
                Nodo X = Nodo(Y);
                X.k++;
                X.supers_usados[i]++;
                X.coste = Y.coste + productos_super[i][X.k];
                
                if(X.k < num_products - 1){
                    X.coste_estimado = calcular_minimo_desdek(suma_minima_acc, X.k + 1, X.coste);
                }
                else{
                    X.coste_estimado = X.coste;
                }

                if(X.coste_estimado < mejor_coste){
                    if(X.k == num_products-1){
                        mejor_coste = X.coste_estimado;
                    }
                    else{
                        pq.push(X);
                    }
                }
            }
        }
    }

    return mejor_coste;
}

bool resolver(){
    int supers, productos;
    cin >> supers >> productos;
    
    Matriz<int> productos_super(supers, productos, 0);

    for (int i = 0; i < supers; i++)
    {
        for (int j = 0; j < productos; j++)
        {
            cin >> productos_super[i][j];
        }
        
    }
    
    vector<int> suma_minima_acc(productos, 0);
    suma_minima_acc[productos-1] = calcular_min_columna(productos_super, productos-1);

    for (int i = productos-2; i >= 0; i--)
    {
        suma_minima_acc[i] = suma_minima_acc[i+1] + calcular_min_columna(productos_super, i);
        // cout << suma_minima_acc[i] << endl;
    }
    

    int sol = asignar(productos_super, suma_minima_acc);
    
    cout << sol << endl;

    return true;
}




int main() {
    // #ifndef DOMJUDGE
    // ifstream in("input.in");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf());
    // #endif
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        resolver();
    }
    
    // #ifndef DOMJUDGE
    // cin.rdbuf(cinbuf);
    // system("PAUSE");
    // #endif
   return 0;
}


