#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
#include "EnterosInf.h"
#include <sstream>


using namespace std;
using lli = long long int;

struct Movie {
    int start_hour;
    int duration;
};


int max_movie_time(vector<Movie>& movies, int num_movies) {
    int maximo = 0;
    // Calcular los máximos tiempos
   
    int N = num_movies;
    vector<int> memo(N, 0); // Inicializa el vector memo con valores 0
    for (int i = N - 1; i >= 0; i--) {
        int init = movies[i].start_hour + movies[i].duration + 10;
        for (int j = i + 1; j < N; j++) { // Busca la película que empieza después de que acabe la i-ésima película
            if (movies[j].start_hour >= init) {
                memo[i] = max(memo[i], memo[j]);
            }
        }
        memo[i] += movies[i].duration; //memo[i] es el tiempo máximo que se puede ver de películas a partir de la i-ésima película
    }
    int max_val = 0;
    for (int i = 0; i < N; i++) {
        max_val = max(max_val, memo[i]);
    }
    return max_val;
}



bool resuelveCaso() {
    int num_movies;

    cin >> num_movies;
    if (num_movies == 0) {
        return false;
    }

    vector<Movie> movies(num_movies);
    for (int i = 0; i < num_movies; ++i) {
        string time;
        cin >> time >> movies[i].duration;

        // Procesar la hora en formato HH:MM
        int hour, minute;
        char delimiter;
        stringstream ss(time);
        ss >> hour >> delimiter >> minute;
        movies[i].start_hour = hour * 60 + minute; // Convertir la hora a minutos
    }

    sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        if (a.start_hour < b.start_hour) {
            return true;
        }
        else if (a.start_hour == b.start_hour && a.duration < b.duration) {
            return true;
        }
        else {
            return false;
        }
        }
    );


    int max_time = max_movie_time(movies, num_movies);
    cout << max_time << "\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std :: cin to casos .
#endif
    //int numCasos;
    //cin >> numCasos;
    //for (int i = 0; i < numCasos; ++i)
    //{
    //    resuelveCaso(); std::cin.ignore();
    //}
    while (resuelveCaso()) {

    }
    // Para restablecer entrada . Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system(" PAUSE ");
#endif
    return 0;

}
