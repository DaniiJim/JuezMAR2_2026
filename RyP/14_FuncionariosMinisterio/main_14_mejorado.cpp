#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include "Matriz.h"

using namespace std;

/*
1. Representacion de las soluciones  
   Cada solucion se representa como una tupla (x₀, x₁, ..., xₙ₋₁) donde:
   - xᵢ es el indice del trabajo asignado al funcionario i, ya que cada trabajo se asigna a un unico funcionario

3. Arbol de exploracion  
   - Cada nodo representa una asignacion parcial de trabajos a funcionarios hasta el nivel k
   - Se utiliza una cola de prioridad (priority_queue) para expandir el nodo mas prometedor
   - En el nivel k decidimos que trabajo asignar al funcionario k
   - Se lleva un vector marcas_trabajos[j] que marca si el trabajo j ya ha sido asignado

4. Funcion de estimacion  
   La estimacion es una cota inferior del tiempo total:
        estimacion = tiempo_acumulado + estimaciones[k]
        Donde estimaciones[k] representa la suma de los tiempos minimos posibles para asignar los trabajos restantes a partir del nivel k 
        Esto garantiza que la estimacion nunca es menor que el coste real de ninguna solucion alcanzable desde el nodo actual

5. Criterios de poda  
   Se descartan los nodos cuyo coste estimado ya es peor que la mejor solucin encontrada:
        - Si estimacion ≥ mejor_tiempo --> se poda
        Esto evita explorar ramas del arbol que no pueden conducir a una mejor solucion

6. Llamada inicial y expansion  
   - Se genera la raiz con k = 0, tiempo = 0, y sin trabajos asignados
   - En cada nivel se asigna un trabajo distinto a cada funcionario
   - Los hijos se generan asignando a funcionario k un trabajo j no usado
   - Se actualiza el tiempo, el vector de usados y la estimacion
   - Si se alcanza el nivel n (todos los funcionarios tienen trabajo), se actualiza la mejor solucion si mejora el tiempo minimo

7. Coste
   - Coste temporal: en el peor caso se exploran n! permutaciones, pero gracias a la poda el espacio de busqueda se reduce significativamente
   - Coste espacial: se utiliza una priority_queue con nodos, cada uno con vectores de tamanyo n. El espacio depende del numero de nodos vivos, pero es O(n × nodos_vivos)
*/

struct Nodo {
    vector<int> asignacion;         //Trabajo asignado al funcionario i
    vector<bool> marcas_trabajos;   //Vector de marcas para los trabajos
    int k;          //Nivel del arbol, lo mismo que el numero de funcoianrios asignados hasta el momento
    int tiempo;     //Suma de tiempos de los trabajos asignados
    int coste_estimado;     //Criterio de prioridad de la cola. Coste_estimado = tiempo + cota_inferior


    //Sobrecargar operador para que la cola funcione como una cola de minimos
    bool operator<(const Nodo& otro) const {
        return otro.coste_estimado < coste_estimado;
    }
};


//Calcula el mejor tiempo minimo para resolver cada tarea
vector<int> calcular_estimaciones(const Matriz<int>& M) {
    int N = M.numfils();

    //Se encuentra el tiempo minimo en el que se podria realizar cada trabajo
    vector<int> minimos(N);
    for (int j = 0; j < N; ++j) {
        int minimo = M[0][j];
        for (int i = 1; i < N; ++i)
            minimo = min(minimo, M[i][j]);
        minimos[j] = minimo;
    }

    //Calculo del tiempo acumulado
    /*
	Ejemplo de calculo acumulado:
		aux_minimos = [10, 10, 10]
		resultado = [30, 20, 10]
	Eso significa que si estamos en el nivel 0, la mejor estimacion de tiempo restante es 30
	Si estamos en el nivel 1, el tiempo minimo restante es 20, etc.
	*/
    vector<int> estimaciones(N + 1, 0);
    for (int i = N - 1; i >= 0; --i)
        estimaciones[i] = estimaciones[i + 1] + minimos[i];

    return estimaciones;
}

int asignar_funcionarios(const Matriz<int>& M, const vector<int>& estimaciones) {
    int N = M.numfils();
    priority_queue<Nodo> cola;  //Cola de prioridad de minimos de los nodos vivos


    //En el nodo raiz no hay trabajos asignados todavia
    Nodo raiz;
    raiz.k = 0;
    raiz.tiempo = 0;
    raiz.asignacion = vector<int>(N, -1);
    raiz.marcas_trabajos = vector<bool>(N, false);
    raiz.coste_estimado = estimaciones[0];
    cola.push(raiz);

    //int mejor = INT_MAX;
    int mejor = 10000*20;   //Por probar

    while (!cola.empty() && cola.top().coste_estimado < mejor) {
        Nodo actual = cola.top(); cola.pop();

        if (actual.k == N) {    //Si ay se han asignado todos los trabajos
            mejor = min(mejor, actual.tiempo);
        } else {
            //Intentar asignar siguiente trabajo
            for (int t = 0; t < N; t++) {
                if (!actual.marcas_trabajos[t]) {
                    Nodo hijo = actual;                 //Crear nodo hijo copiando al padre
                    hijo.k = actual.k + 1;              //Aumentar nivel
                    hijo.marcas_trabajos[t] = true;     //Marcar trabajo
                    hijo.asignacion[actual.k] = t;      //Funcionario k hace trabajo t
                    hijo.tiempo += M[actual.k][t];      //Se suma el tiempo que se tarda en hacer ese trabajo
                    hijo.coste_estimado = hijo.tiempo + estimaciones[hijo.k];

                    if (hijo.coste_estimado < mejor) {
                        cola.push(hijo);
                    }
                }
            }
        }
    }

    return mejor;
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    Matriz<int> M(N, N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> M[i][j];

    vector<int> estimaciones = calcular_estimaciones(M);
    cout << asignar_funcionarios(M, estimaciones) << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
