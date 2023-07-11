#include <stdio.h>
#include <omp.h>
#include <math.h>

#define largImagem 100
#define alturaImagem 100
#define BIN_COUNT 256
#define MAX_VALUE 256
#define NUM_THREADS 4

int img[largImagem][alturaImagem];
int histogram[BIN_COUNT];

int main() {
    int i, j, idItensidade;

    // Preenchimento da matriz img com valores de exemplo
    for (i = 0; i < largImagem; i++) {
        for (j = 0; j < alturaImagem; j++) {
            img[i][j] = (i + j) % MAX_VALUE;
        }
    }

    // Go through our matrix and start binning values
    #pragma omp parallel for collapse(2) num_threads(NUM_THREADS)
    for (i = 0; i < largImagem; i++) {
        for (j = 0; j < alturaImagem; j++) {
            idItensidade = floor((BIN_COUNT - 1) * (img[i][j] / (MAX_VALUE - 1)));

            // Utilize uma redução para garantir operações atômicas e evitar condições de corrida
            #pragma omp atomic
            histogram[idItensidade]++;
        }
    }

    // Imprimir o histograma resultante
    for (i = 0; i < BIN_COUNT; i++) {
        printf("Histogram[%d]: %d\n", i, histogram[i]);
    }

    return 0;
}
