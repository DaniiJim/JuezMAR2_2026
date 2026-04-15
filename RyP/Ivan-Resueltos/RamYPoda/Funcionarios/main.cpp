#include <iostream>
#include <vector>
#include <queue>
#include "Matriz.h"
using namespace std;


struct Nodo{
    int k;                                          // Funcionario procesandose
    int tiempo;
    // int mejorTiempo;                                // MejorTiempo hasta el momento
    vector<bool> caminos_asignados;                // Vector con las tareas asignadas hasta el momento
    int coste_estimado;                             // coste estimado para ordenar los nodos de la cola de prioridad

    bool operator<(const Nodo& otro) const{
        return otro.coste_estimado < coste_estimado;
    }
};

int calcular_minimo_fila(const Matriz<int>& funcionario_trabajo, int k){
    int minimo = funcionario_trabajo[k][0];
    int N = funcionario_trabajo.numcols();
    for (int i = 0; i < N; i++)
    {
        minimo = min(minimo, funcionario_trabajo[k][i]);
    }
    return minimo;
}

int calcular_minimo_acumulado(const vector<int>& suma_minima_acc, int k, int tiempo){
    return suma_minima_acc[k] + tiempo;
}


int asignar_funcionarios(const Matriz<int>& funcionarios_trabajo, const vector<int>& suma_minima_acc){
    priority_queue<Nodo> pq;
    int N = funcionarios_trabajo.numfils();
    Nodo Y;
    // Y.mejorTiempo = INT32_MAX;
    Y.k = -1;
    Y.tiempo = 0;
    Y.caminos_asignados = vector<bool>(N, false);
    Y.coste_estimado = calcular_minimo_acumulado(suma_minima_acc, Y.k, Y.tiempo);
    int mejor_tiempo = INT32_MAX;
    pq.push(Y);


    while(!pq.empty() && pq.top().coste_estimado < mejor_tiempo){
        Y = pq.top();
        pq.pop();
        Nodo X = Nodo(Y);
        X.k++;

        for (int i = 0; i < N; i++)
        {
            if(!X.caminos_asignados[i]){
                X.caminos_asignados = Y.caminos_asignados;
                X.caminos_asignados[i] = true;
                X.tiempo = Y.tiempo + funcionarios_trabajo[X.k][i];
                
                if(X.k < N-1){
                    X.coste_estimado = calcular_minimo_acumulado(suma_minima_acc, X.k+1, X.tiempo);
                }
                else{
                    X.coste_estimado = X.tiempo;    
                }

                if(X.coste_estimado < mejor_tiempo){
                    if(X.k == N-1){
                        mejor_tiempo = X.coste_estimado;
                    }
                    else{
                        // cout << "Coste Estimado del Nodo X: " + X.coste_estimado << endl;
                        // cout << "Tiempo del Nodo X: " + X.tiempo << endl;

                        pq.push(X);
                    }    
                }
            }
            
        }
        



    }

    return mejor_tiempo;
}

bool resolver(){
    int N;
    cin >> N;
    if(N == 0)
        return false;
    Matriz<int> funcionario_trabajo(N, N, 0);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> funcionario_trabajo[i][j];
        }
        
    }
    
    vector<int> suma_min_acc(N, 0);
    suma_min_acc[N-1] = calcular_minimo_fila(funcionario_trabajo, N-1);

    for (int i = N-2; i >= 0; i--)
    {
        suma_min_acc[i] = suma_min_acc[i+1] + calcular_minimo_fila(funcionario_trabajo, i);
    }

    int sol = asignar_funcionarios(funcionario_trabajo, suma_min_acc);

    cout << sol << endl;

    return true;
}




int main() {
    // #ifndef DOMJUDGE
    // ifstream in("input.in");
    // auto cinbuf = std::cin.rdbuf(in.rdbuf());
    // #endif
    while (resolver());
//     #ifndef DOMJUDGE
//    cin.rdbuf(cinbuf);
//    system("PAUSE");
//     #endif
   return 0;
}


