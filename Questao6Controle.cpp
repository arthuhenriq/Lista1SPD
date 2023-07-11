#include <iostream>
#include <omp.h>
#include <cmath>
#include <chrono>

#define NUM_THREADS 6

// Crivo de Eratostenes em OpenMP Controle

using namespace std;

bool* crivoEratostenes(long n) {
    bool* primos = new bool[n + 1];

    for(long i = 2; i <= n; i++) {
        primos[i] = true;
    }

    #pragma omp parallel sections shared(primos) num_threads(NUM_THREADS)
    {
        #pragma omp section
        for(long i = 2; i < n; i++) {
            if(primos[i]) {
                for(long j = i; j * i <= n; j++) {
                    primos[i * j] = false;
                }
            }
        }
    }



    return primos;
}

void mostrarPrimos(bool* primos, long n) {
    long qntPrimos = 0;

    #pragma omp parallel for reduction(+:qntPrimos)
    for(long i = 2; i <= n; i++) {
        if(primos[i]) {
            cout << " " << i << " "  ;
            qntPrimos++;
        }
    }
    cout << endl << "Quantidade de primos: " << qntPrimos;
}

int main() {
    chrono::high_resolution_clock::time_point tempo1 = chrono::high_resolution_clock::now();
    long n = 10000L;
    bool* primos = crivoEratostenes(n);
    mostrarPrimos(primos, n);
    delete[] primos;
    chrono::high_resolution_clock::time_point tempo2 = chrono::high_resolution_clock::now();
    cout << "\tTempo = " << (chrono::duration_cast<chrono::nanoseconds>(tempo2 - tempo1).count()/1000000) << " ms";
    return 0;
}
