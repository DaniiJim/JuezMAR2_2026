#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <numeric>
#include <limits>
using namespace std;
const int INFINITO = numeric_limits<int>::max();

struct tDatos {
    int n, m;
    vector<int> demanda;
    vector<int> stock;
    vector<int> precio;
};


struct Nodo {
    vector<int> demanda_nodo;   //Demanda restante por facultad
    int mascarillasRestantes;
    int k;                      //Nivel --> Suministrador actual
    int coste;
    int estimacion_precio;

    bool operator<(const Nodo& otro) const {
        return otro.estimacion_precio < estimacion_precio;    //Se ordenan por menor estimacion (precio)
    }
};


//Funcion de estimacion optimista, calcula una cota del menor coste posible que se puede alcanzar desde el nodo actual
int estimacionOptimista(const Nodo& nodo, const tDatos& datos) {
    int estimacion = nodo.coste;        //Coste acumulado hasta en ese nodo
    int faltan = nodo.mascarillasRestantes;    //Mascarillas que faltan por asignar

    //Desde el suministrador actual "k" en adelante, se intenta cubrir las que faltan --> AL PRECIO MAS BARATO
    for (int i = nodo.k; i < datos.m && faltan > 0; ++i) {
        int num_mascarillas = min(faltan, datos.stock[i]);
        estimacion += num_mascarillas * datos.precio[i];
        faltan -= num_mascarillas;
    }
    return estimacion;
}

int resolver(const tDatos& datos) {
    Nodo raiz;
    raiz.demanda_nodo = datos.demanda;
    raiz.mascarillasRestantes = accumulate(datos.demanda.begin(), datos.demanda.end(), 0);
    raiz.k = 0;
    raiz.coste = 0;
    raiz.estimacion_precio = estimacionOptimista(raiz, datos);

    priority_queue<Nodo> cola;
    cola.push(raiz);
    int mejor_precio = INFINITO; //Infinito porque queremos minimizar

    while (!cola.empty() && cola.top().estimacion_precio < mejor_precio) {

        //Se saca el nodo con mejor estimacion (menor)
        Nodo act = cola.top(); cola.pop();

        if (act.mascarillasRestantes == 0) {
            mejor_precio = min(mejor_precio, act.coste);
        } 
        else if (act.k < datos.m) {

            // NO USAR ESE SUMINISTRADOR
            Nodo sinUsar = act;
            sinUsar.k++;
            sinUsar.estimacion_precio = estimacionOptimista(sinUsar, datos);
            if (sinUsar.estimacion_precio < mejor_precio)
                cola.push(sinUsar);

            // USAR SUMINISTRADOR K
            for (int i = 0; i < datos.n; ++i) { //Recorrer facultades
                if (act.demanda_nodo[i] != 0){  //Comprobar que se necesitan mascarillas                    

                    //Se calcula la cantidad de mascarillas que el suministrador "k" puede dar a la facultad "i"
                    int cantidad = min(datos.stock[act.k], act.demanda_nodo[i]);
                    if (cantidad != 0){

                        //Nuevo nodo para explorar esa opcion
                        Nodo hijo = act;
                        hijo.k++;
                        hijo.demanda_nodo[i] -= cantidad;
                        hijo.mascarillasRestantes -= cantidad;
                        hijo.coste += cantidad * datos.precio[act.k];

                        // ESTIMACION Y PODA
                        hijo.estimacion_precio = estimacionOptimista(hijo, datos);
                        if (hijo.estimacion_precio < mejor_precio)
                            cola.push(hijo);
                    }
                }
            }
        }
    }

    return mejor_precio;
}

bool resuelveCaso() {
    tDatos datos;
    cin >> datos.n >> datos.m;
    if (!cin) return false;

    datos.demanda = vector<int>(datos.n);
    datos.stock = vector<int>(datos.m);
    datos.precio = vector<int>(datos.m);

    for (int i = 0; i < datos.n; ++i) cin >> datos.demanda[i];
    for (int i = 0; i < datos.m; ++i) cin >> datos.stock[i];
    for (int i = 0; i < datos.m; ++i) cin >> datos.precio[i];

    int mejor = resolver(datos);

    if (mejor == INFINITO)
        cout << "NO\n";
    else
        cout << mejor << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;
    while (casos--) resuelveCaso();

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
