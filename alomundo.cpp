#include <iostream>
#include <omp.h>

using namespace std;

int main (int argc, char *argv[])
{
    int qtdThreads, id;

    #pragma omp parallel private(qtdThreads, id)
    {
        id = omp_get_thread_num();
        cout << "\nAlo mundo! Thread = " << id;
    
        if (id == 0) //apenas a thread principal
        {
            qtdThreads = omp_get_num_threads();
            cout << "\nNumero de threads = " << qtdThreads;
        }
    } 
    cout << endl;
    
    return 0;
}
