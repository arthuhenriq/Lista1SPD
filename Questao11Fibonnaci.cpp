#include <iostream>
#include <omp.h>

using namespace std;

#define NUM_THREADS 6

// Programa criado para realizar  a sequência Fibonnaci em OpenMP


int main() {
    long long n; // O valor m�ximo da sequ�ncia Fibonacci
    long double penult = 1, ult = 0; // Inicializa��o dos primeiros dois n�meros da sequ�ncia
    long double temp;

    cout << "Exibir quantos termos na sequencia Fibonnaci: ";
    cin >> n;

    cout << ult << " " << penult;

    #pragma omp parallel for num_threads(NUM_THREADS)
    for (long long aux = 3; aux <= n; aux++) {
        #pragma omp critical
        {
            cout << " " << (ult + penult);
        }

        temp = ult;
        ult = penult;
        penult = penult + temp;
    }

    cout << endl;

    return 0;
}
