#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
	int M[20][20];
	int n;
}tDatos;


void resolver(const tDatos& datos, const vector<int>& tiempoMinTrabajoRestante,
	int indice_trabajo, vector<bool>& marcas_funcionarios, int tiempo_total, int& tiempo_min){


	//Para el trabajo actual se recorren todos los funcionarios
	for (int k = 0; k < datos.n; k++) {

		if (marcas_funcionarios[k] == false) {
			// Asignar temporalmente el trabajo al funcionario k
			tiempo_total += datos.M[k][indice_trabajo];
			marcas_funcionarios[k] = true;

			// Si todos los trabajos estan asignados se comprueba si es solucion
			if (indice_trabajo == datos.n - 1) {
				tiempo_min = min(tiempo_min, tiempo_total);
			}
			else {
				// Se comprueba si se puede mejorar la solucion
				if (tiempo_total + tiempoMinTrabajoRestante[indice_trabajo + 1] < tiempo_min)
					resolver(datos, tiempoMinTrabajoRestante, indice_trabajo + 1, marcas_funcionarios, tiempo_total, tiempo_min);
			}

			// Se quita para probar el resto de combinaciones
			marcas_funcionarios[k] = false;
			tiempo_total -= datos.M[k][indice_trabajo];
		}
	}
}


vector<int> cotaInferiorTiempos(const tDatos& datos)
{
	vector<int> tiempoMinTrabajo(datos.n, 0);
	vector<int> aux_minimos(datos.n, 0);

	// Tiempo minimo necesario para cada trabajo
	for (int i = 0; i < datos.n; i++) {
		aux_minimos[i] = datos.M[0][i];
		for (int j = 1; j < datos.n; j++) {
			aux_minimos[i] = min(aux_minimos[i], datos.M[j][i]);	//Recorrer la columna hacia abajo
		}
	}

	int suma_tiemposmin = 0;
	/*
	Se recorre de derecha a izquierda para que cada resultado[i] represente
	la cota inferior del futuro (es decir, cuánto falta por asignar en el peor caso)
	*/
	for (int i = datos.n - 1; i >= 0; i--) {
		suma_tiemposmin = suma_tiemposmin + aux_minimos[i];
		tiempoMinTrabajo[i] = suma_tiemposmin;
	}

	/*
	Ejemplo de calculo acumulado:
		aux_minimos = [10, 10, 10]
		resultado = [30, 20, 10]
	Eso significa que si estamos en el nivel 0, la mejor estimacion de tiempo restante es 30
	Si estamos en el nivel 1, el tiempo minimo restante es 20, etc.
	*/
	return tiempoMinTrabajo;
}


bool resuelveCaso() {
	tDatos datos;
	cin >> datos.n;
	if (datos.n == 0) return false;

	for (int i = 0; i < datos.n; i++) {
		for (int j = 0; j < datos.n; j++) {
			cin >> datos.M[i][j];
		}
	}

	vector<bool> marcas(datos.n, false);
	int tiempo_total = 0;
	int tiempo_minimo = 10000 * datos.n;	//Maximo valor posible
	int cont = 0;	//Se empieza desde el primer trabajo
	vector<int> tiempoMinTrabajoRestante = cotaInferiorTiempos(datos);

	resolver(datos, tiempoMinTrabajoRestante, cont, marcas, tiempo_total, tiempo_minimo);

	cout << tiempo_minimo << "\n";
	return true;
}



int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());


    /*
    unsigned int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
    */


    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
