#include <iostream>

#define MATRIX_SIZE 5

void Transponse(int** m) {
    const int n = MATRIX_SIZE;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            m[i][j]                 ^= m[n - 1 - j][n - 1 - i];
            m[n - 1 - j][n - 1 - i] ^= m[i][j];
            m[i][j]                 ^= m[n - 1 - j][n - 1 - i];
        }
    }
}

int ColAvg(int** m, int c) {
    int avg = 0;
    for(int i = 0; i < MATRIX_SIZE; i++) {
        avg += m[i][c];
    }
    return avg / MATRIX_SIZE;
}

int CntAvgLower(int** m, int target_avg) {
    int cnt = 0;
    for(int i = 0; i < MATRIX_SIZE; i++) {
        if(ColAvg(m, i) < target_avg) {
            cnt++;
        }
    }
    return cnt;
}

void PrintMatrix(int** m) {
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Выделение памяти под массив
    int** m = new int*[MATRIX_SIZE];
    for(int i = 0; i < MATRIX_SIZE; i++) {
        m[i] = new int[MATRIX_SIZE];
    }

    std::cout << "Enter matrix 5x5:\n";

    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            //m[i][j] = i+j;
            std::cin >> m[i][j];
        }
    }

    std::cout << "Matrix:\n";
    PrintMatrix(m);

    std::cout << "Transposed:\n";
    Transponse(m);
    PrintMatrix(m);

    int avg;
    std::cout << "Enter num: ";
    std::cin >> avg;
    std::cout << CntAvgLower(m, avg);

    delete[] m;

    return 0;
}
