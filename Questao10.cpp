#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <chrono>

using namespace std;

// Programa criado para resgatar os dois maiores números de um conjunto

int main() {

    int n;

    auto t1 = chrono::high_resolution_clock::now();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 20000);

    cout << "Digite o tamanho do conjunto: ";
    cin >> n;

    vector<int> numbers(n);

    for (int i = 0; i < n; i++) {
        numbers[i] = dist(gen);
    }

    for (int i = 0; i < n; i++) {
        cout << numbers[i] << " ";
    }

    cout << endl;

    int largest1 = numbers[0], largest2 = numbers[0];


    for (int i = 1; i < numbers.size(); i++) {
        int num = numbers[i];

        {
            if (num > largest1) {
                largest2 = largest1;
                largest1 = num;
            }
            if (num > largest2 && num < largest1) {
                largest2 = num;
            }
        }
    }

    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds> (t2 - t1).count();

    cout << endl;
    cout << "Os dois maiores numeros sao: " << largest1 << " e " << largest2 << endl;
    cout << "\nTempo de execucao do algoritmo: "  << duration << " (us)." << endl;

    return 0;
}
