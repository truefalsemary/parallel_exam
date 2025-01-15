#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <clocale>

const int SIZE = 10'000'000;

void generateRandomArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000 + 1;
    }
}

int findMaxSequential(const int* arr, int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int findMaxParallel(const int* arr, int size) {
    int max_val = arr[0];

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int* arr = new int[SIZE];
    srand(static_cast<unsigned int>(time(0))); 

    generateRandomArray(arr, SIZE);

    double start_time = omp_get_wtime();
    int max_seq = findMaxSequential(arr, SIZE);
    double end_time = omp_get_wtime();
    printf("Последовательный максимум: %d, Время: %.6f секунд\n", max_seq, end_time - start_time);

    start_time = omp_get_wtime();
    int max_par = findMaxParallel(arr, SIZE);
    end_time = omp_get_wtime();
    printf("Параллельный максимум: %d, Время: %.6f секунд\n", max_par, end_time - start_time);

    delete[] arr;

}
