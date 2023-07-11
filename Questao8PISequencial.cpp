#include<chrono>
#include<iostream>
#include<iomanip>
#include <omp.h>

#define NUM_THREADS 6

using namespace std;

// Programa criado para prever o próximo número de PI Sequencial


int main() {
    long long num_steps = 100000000;
    long double step;
    long double x, pi, sum = 0.0;

    cout << "Calculando o valor de PI para " << num_steps << " passos...";
    auto t1 = chrono::high_resolution_clock::now();
    step = 1.0 / (long double)num_steps;

    for(long long i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x*x);
    }
    pi = step * sum;

    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

    cout << "\nValor aproximado = " << setprecision(50) << pi;
    cout << "\nTempo de execucao do algoritmo (ms) = " << duration;
}
