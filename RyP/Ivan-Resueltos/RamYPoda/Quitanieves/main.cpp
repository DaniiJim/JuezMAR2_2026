#include <iostream>
#include <vector>
#include <queue>
#include "Matriz.h"
using namespace std;


struct Nodo{
    int k;                                          // Funcionario procesandose
    int coste;
    vector<bool> caminos_asignados;                // Vector con las tareas asignadas hasta el momento
    int coste_estimado;                             // coste estimado para ordenar los nodos de la cola de prioridad

    bool operator<(const Nodo& otro) const{
        return coste_estimado < otro.coste_estimado;
    }
};

int calcular_max_fila(const Matriz<int>& funcionario_trabajo, int k){
    int maximo = funcionario_trabajo[k][0];
    int N = funcionario_trabajo.numcols();
    for (int i = 0; i < N; i++)
    {
        maximo = max(maximo, funcionario_trabajo[k][i]);
    }
    return maximo;
}

int calcular_maximo_acumulado(const vector<int>& suma_maxima_acc, int k, int coste){
    if (k < 0) {
        return suma_maxima_acc[0] + coste;
    }
    return suma_maxima_acc[k] + coste;
}

int cota_pesimista(const Matriz<int>& carros_caminos, const vector<int>& anchuras_carros, const vector<int>& anchuras_caminos, const Nodo& nodo){
    int N = carros_caminos.numfils();
    int M = carros_caminos.numcols();
    vector<bool> usados = nodo.caminos_asignados;
    int coste = nodo.coste;

    for (int fila = nodo.k + 1; fila < N; fila++)
    {
        int mejor_columna = -1;
        int mejor_valor = INT32_MIN;

        for (int columna = 0; columna < M; columna++)
        {
            if (!usados[columna] && anchuras_carros[fila] <= anchuras_caminos[columna] && carros_caminos[fila][columna] > mejor_valor)
            {
                mejor_valor = carros_caminos[fila][columna];
                mejor_columna = columna;
            }
        }

        if (mejor_columna == -1)
        {
            return INT32_MIN;
        }

        usados[mejor_columna] = true;
        coste += mejor_valor;
    }

    return coste;
}


int asignar_funcionarios(const Matriz<int>& carros_caminos, const vector<int>& anchuras_carros, const vector<int>& anchuras_caminos, const vector<int>& suma_maxima_acc){
    priority_queue<Nodo> pq;
    int N = carros_caminos.numfils();
    int M = carros_caminos.numcols();
    Nodo Y;
    // Y.mejorTiempo = INT32_MAX;
    Y.k = -1;
    Y.coste = 0;
    Y.coste_estimado = calcular_maximo_acumulado(suma_maxima_acc, Y.k + 1, Y.coste);
    Y.caminos_asignados = vector<bool>(M, false);
    int mejor_coste = cota_pesimista(carros_caminos, anchuras_carros, anchuras_caminos, Y);
    if (mejor_coste == INT32_MIN)
    {
        return mejor_coste;
    }
    pq.push(Y);


    while(!pq.empty() && pq.top().coste_estimado > mejor_coste){
        Y = pq.top();
        pq.pop();
        Nodo X = Nodo(Y);
        X.k++;
        // cout << "LLego hasta aqui";
        for (int i = 0; i < M; i++)
        {
            if(!X.caminos_asignados[i] && anchuras_carros[X.k] <= anchuras_caminos[i]){
                X.caminos_asignados = Y.caminos_asignados;
                X.caminos_asignados[i] = true;
                X.coste = Y.coste + carros_caminos[X.k][i];
                // cout << "LLego hasta aqui";
                if(X.k < N-1){
                    X.coste_estimado = calcular_maximo_acumulado(suma_maxima_acc, X.k+1, X.coste);
                }
                else{
                    X.coste_estimado = X.coste;    
                }

                if(X.coste_estimado > mejor_coste){
                            // cout << "LLego hasta aqui";
                    if(X.k == N-1){
                        mejor_coste = X.coste_estimado;
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

    return mejor_coste;
}

bool resolver(){
    int N, M;
    cin >> N >> M;
    vector<int> anchuras_carros(N);
    vector<int> anchuras_caminos(M);

    for (int i = 0; i < N; i++)
    {
        cin >> anchuras_carros[i];
    }
    
    for (int i = 0; i < M; i++)
    {
        cin >> anchuras_caminos[i];
    }
    
    Matriz<int> carros_caminos(N, M, 0);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> carros_caminos[i][j];
        }
        
    }
    
    vector<int> suma_max_acc(N, 0);
    suma_max_acc[N-1] = calcular_max_fila(carros_caminos, N-1);

    for (int i = N-2; i >= 0; i--)
    {
        suma_max_acc[i] = suma_max_acc[i+1] + calcular_max_fila(carros_caminos, i);
    }

    int sol = asignar_funcionarios(carros_caminos, anchuras_carros, anchuras_caminos, suma_max_acc);

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


