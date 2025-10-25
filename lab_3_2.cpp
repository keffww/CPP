#include <iostream> 
void my_sort(int n, int* array) {
    if (n <= 1) {
        return;
    }
    int mid = n / 2;
    int left_size = mid;
    int right_size = n - mid;
    int* left = new int[left_size];
    int* right = new int[right_size];
    for (int i = 0; i < left_size; i++) {
        left[i] = array[i];
    }
    for (int i = 0; i < right_size; i++) {
        right[i] = array[mid + i];
    }
    // Рекурсивно сортируем обе половины
    my_sort(left_size, left);
    my_sort(right_size, right);
    
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < left_size) {
        array[k] = left[i];
        i++;
        k++;
    }
    while (j < right_size) {
        array[k] = right[j];
        j++;
        k++;
    }
    delete[] left;
    delete[] right;
}

int main() {
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int n = 9;
    
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    // Сортируем массив
    my_sort(n, arr);
    
    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    return 0;
}