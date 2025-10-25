// merge_sort_benchmark.cpp
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

void my_sort(int n, int* array) {
    if (n <= 1) return;
    
    int mid = n / 2;
    int left_size = mid;
    int right_size = n - mid;
    
    int* left = new int[left_size];
    int* right = new int[right_size];
    
    for (int i = 0; i < left_size; i++)
        left[i] = array[i];
    for (int i = 0; i < right_size; i++)
        right[i] = array[mid + i];
    
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

// Функция для генерации случайного массива
int* generate_random_array(int n) {
    int* arr = new int[n];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Функция для проверки корректности сортировки
bool is_sorted(int n, int* arr) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

int main() {
    // Размеры массивов для тестирования
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    std::cout << "Замеры времени выполнения сортировки слиянием:\n";
    std::cout << "Размер массива\tВремя (мс)\tO(n log n)\n";
    std::cout << "--------------------------------------------\n";
    
    // Файл для сохранения результатов
    std::ofstream data_file("sorting_data.csv");
    data_file << "n,time_ms,n_log_n\n";
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* arr = generate_random_array(n);
        
        // Замер времени
        auto start = std::chrono::high_resolution_clock::now();
        my_sort(n, arr);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        double time_ms = duration.count();
        
        // Вычисляем n*log(n) для сравнения
        double n_log_n = n * log2(n);
        
        // Проверяем корректность сортировки
        bool sorted = is_sorted(n, arr);
        
        std::cout << n << "\t\t" << time_ms << " мс\t\t" << (sorted ? "OK" : "ERROR") << std::endl;
        
        // Сохраняем данные в файл
        data_file << n << "," << time_ms << "," << n_log_n << "\n";
        
        delete[] arr;
    }
    
    data_file.close();
    std::cout << "\nДанные сохранены в файл 'sorting_data.csv'\n";
    
    return 0;
}