#include<iostream>
#include<omp.h>

using namespace std;

// Programa criado para realizar a multiplicação de duas matrizes paralelo em OpenMp

double MA[4][4], MB[4][4], MC[4][4];
int i, row, col, size = 4;

int main() {

    for(row = 0; row < size; row++) {
            for(col = 0; col < size; col++){
                MA[row][col] = rand();
                MB[row][col] = rand();
            }
        }

    for(row = 0; row < size; row++) {
            for(col = 0; col < size; col++){
                cout << " " << MA[row][col];
            }
            cout << endl;
        }

    cout << endl << endl;

    #pragma omp parallel sections shared(MA, MB, MC, size) private(row,col,i)
    {
        #pragma omp section
    {
        for(row = 0; row < size; row++) {
            for(col = 0; col < size; col++){
                MC[row][col] = 0.0;
            }
        }
    }


        #pragma omp section
        {
            for(row = 0; row < size; row++) {
            for(col = 0; col < size; col++){
                for(i = 0; i < size; i++) {
                    MC[row][col] += MA[row][i] * MB[i][col];
                }
            }
        }
        }

    }

    for(row = 0; row < size; row++) {
            for(col = 0; col < size; col++){
                cout << " " << MC[row][col];
            }
            cout << endl;
        }
}
