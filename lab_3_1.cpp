#include <iostream>
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/**
 Сортирует массив по заданному алгоритму 
 @param n -- размер массива
 @param array -- указатель на массив
 */
void my_sort(int n, int* array) {
    // Построение кучи
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // Извлечение элементов из кучи
    for (int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int main() {
    int arr[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    
    my_sort(n, arr);
    for (int i = 0; i<n; i++){
        std::cout << arr[i] << std::endl;
    }
    return 0;
}