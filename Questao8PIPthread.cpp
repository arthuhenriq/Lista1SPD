#include <chrono>
#include <iostream>
#include <iomanip>
#include <pthread.h>

using namespace std;

const int NUM_THREADS = 6;

// Programa criado para prever o próximo número de PI em pThread

struct ThreadData {
    long long start;
    long long end;
    long double sum;
};

void* thread_func(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    long double step = 1.0 / (long double)(data->end - data->start);

    for (long long i = data->start; i < data->end; i++) {
        long double x = (i + 0.5) * step;
        data->sum += 4.0 / (1.0 + x*x);
    }

    pthread_exit(NULL);
}

int main() {
    long long num_steps = 100000000;
    long double pi = 0.0;
    auto t1 = chrono::high_resolution_clock::now();

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    long long chunk_size = num_steps / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? num_steps : (i + 1) * chunk_size;
        thread_data[i].sum = 0.0;

        pthread_create(&threads[i], NULL, thread_func, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        pi += thread_data[i].sum;
    }

    long double step = 1.0 / (long double)num_steps;
    pi *= step * 4.0;

    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

    cout << "Valor aproximado = " << setprecision(50) << pi << endl;
    cout << "Tempo de execucao do algoritmo (ms) = " << duration << endl;

    return 0;
}
