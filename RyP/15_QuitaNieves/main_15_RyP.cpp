#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

struct tDatos
{
    vector<int> anch_carros;
    vector<int> anch_caminos;
    vector<vector<int>> calidad;
};

struct Nodo
{
    int k;                  // nivel: carro actual (0..n-1)
    vector<int> asignacion; // camino asignado a cada carro (-1 si no se ha asignado)
    int calidad;            // calidad acumulada actual
    int estimacion_precio;         // cota superior (heurística)
    vector<bool> caminos_usados;

    bool operator<(Nodo const &otro) const
    {
        return otro.estimacion_precio < estimacion_precio; // para max heap
    }
};

int calcular_estimacion_voraz(int k, int calidad_actual,
                              const tDatos &datos,
                              const vector<bool> &camino_usado)
{
    int n = datos.anch_carros.size();
    int m = datos.anch_caminos.size();
    int estimacion = calidad_actual;

    vector<bool> caminos_disponibles = camino_usado;

    for (int i = k + 1; i < n; ++i)
    {
        int mejor_calidad = -1;
        int mejor_camino = -1;

        for (int j = 0; j < m; ++j)
        {
            if (!caminos_disponibles[j] && datos.anch_carros[i] <= datos.anch_caminos[j])
            {
                if (datos.calidad[i][j] > mejor_calidad)
                {
                    mejor_calidad = datos.calidad[i][j];
                    mejor_camino = j;
                }
            }
        }

        if (mejor_camino != -1)
        {
            estimacion += mejor_calidad;
            caminos_disponibles[mejor_camino] = true;
        }
    }

    return estimacion;
}

void quitanieves_rp(const tDatos &inst, int &calidad_mejor)
{
    int n = inst.anch_carros.size();
    int m = inst.anch_caminos.size();

    // Nodo raíz
    Nodo raiz;
    raiz.k = -1;
    raiz.asignacion = vector<int>(n, -1);
    raiz.calidad = 0;
    raiz.caminos_usados = vector<bool>(m, false);

    vector<bool> camino_usado(m, false);
    raiz.estimacion_precio = calcular_estimacion_voraz(raiz.k, 0, inst, camino_usado);

    priority_queue<Nodo> cola;
    cola.push(raiz);
    calidad_mejor = 0;

    while (!cola.empty() && cola.top().estimacion_precio > calidad_mejor)
    {
        Nodo actual = cola.top();
        cola.pop();
        int siguiente_k = actual.k + 1;

        // Caso base: solución completa
        if (siguiente_k == n)
        {
            calidad_mejor = max(calidad_mejor, actual.calidad);
            continue;
        }

        // Marcar caminos ya usados en toda la asignación actual
        vector<bool> caminos_usados_actual(m, false);
        for (int i = 0; i < n; ++i)
        {
            if (actual.asignacion[i] != -1)
                caminos_usados_actual[actual.asignacion[i]] = true;
        }

        // Intentar asignar un camino válido al carro siguiente_k
        for (int j = 0; j < m; ++j)
        {
            if (!actual.caminos_usados[j] && inst.anch_carros[siguiente_k] <= inst.anch_caminos[j]) {
                Nodo hijo;
                hijo.k = siguiente_k;
                hijo.asignacion = actual.asignacion;
                hijo.asignacion[siguiente_k] = j;
                hijo.calidad = actual.calidad + inst.calidad[siguiente_k][j];
            
                hijo.caminos_usados = actual.caminos_usados;
                hijo.caminos_usados[j] = true;
            
                hijo.estimacion_precio = calcular_estimacion_voraz(siguiente_k, hijo.calidad, inst, hijo.caminos_usados);
            
                if (hijo.estimacion_precio > calidad_mejor) {
                    cola.push(hijo);
                }
            }
        }
    }
}

bool resuelveCaso()
{
    int n, m;
    cin >> n >> m;

    if (!cin)
        return false;

    tDatos datos;
    datos.anch_carros.resize(n);
    datos.anch_caminos.resize(m);
    datos.calidad = vector<vector<int>>(n, vector<int>(m));

    // Leer anchuras de los carros
    for (int i = 0; i < n; ++i)
        cin >> datos.anch_carros[i];

    // Leer anchuras de los caminos
    for (int j = 0; j < m; ++j)
        cin >> datos.anch_caminos[j];

    // Leer calidades
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> datos.calidad[i][j];

    int calidad_mejor;
    quitanieves_rp(datos, calidad_mejor);

    cout << calidad_mejor << '\n';

    return true;
}

int main()
{
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    unsigned int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
    {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}