#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

// Crivo de Eratostenes Sequencial

bool* crivoEratostenes(long n) {
    bool* primos = new bool[n + 1];

    for(long i = 2; i <= n; i++) {
        primos[i] = true;
    }

    for(long i = 2; i <= n; i++) {
        if(primos[i]) {
            for(long j = i; j * i <= n; j++) {
                primos[i * j] = false;
            }
        }
    }

    return primos;
}

void mostrarPrimos(bool* primos, long n) {
    long qntPrimos = 0;

    for(long i = 2; i <= n; i++) {
        if(primos[i]) {
            cout << i << " ";
            qntPrimos++;
        }
    }
    cout << endl << "Quantidade de primos: " << qntPrimos;
}

int main() {
    chrono::high_resolution_clock::time_point tempo1 = chrono::high_resolution_clock::now();
    long n = 100;
    bool* primos = crivoEratostenes(n);
    mostrarPrimos(primos, n);
    delete[] primos;
    chrono::high_resolution_clock::time_point tempo2 = chrono::high_resolution_clock::now();
    cout << "\tTempo = " << (chrono::duration_cast<chrono::nanoseconds>(tempo2 - tempo1).count()/1000000) << " ms";
    return 0;
}
