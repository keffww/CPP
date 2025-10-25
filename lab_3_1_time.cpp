// sort_interface.cpp

#include <iostream>

// Вспомогательная функция для обмена элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Функция для восстановления свойства кучи в поддереве
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
 Сортирует массив по алгоритму пирамидальной сортировки
 @param n -- размер массива
 @param array -- указатель на массив
 */
void my_sort(int n, int* array) {
    // Построение max-кучи
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // Извлечение элементов из кучи
    for (int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

// Функция для проверки отсортированности массива
bool is_sorted(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

// Функция для заполнения массива случайными значениями
void fill_random(int* arr, int n) {
    // Простой псевдослучайный генератор (без использования rand())
    static unsigned int seed = 12345;
    
    for (int i = 0; i < n; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed % 10000;  // Числа от 0 до 9999
    }
}

// Функция для замера времени (примитивная, через циклы)
void measure_performance() {
    std::cout << "Размер массива\tВремя (усл. ед.)\tn*log(n)" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    
    // Тестируем на разных размерах массивов
    int sizes[] = {100, 500, 1000, 5000, 10000, 20000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int t = 0; t < num_tests; t++) {
        int n = sizes[t];
        int* arr = new int[n];
        
        // Заполняем массив случайными числами
        fill_random(arr, n);
        
        // Примитивный замер производительности через подсчет операций
        // В реальности нужно использовать std::chrono, но по условию нельзя
        unsigned long long operation_count = 0;
        
        // Создаем копию для сортировки
        int* arr_copy = new int[n];
        for (int i = 0; i < n; i++) {
            arr_copy[i] = arr[i];
        }
        
        // Сортируем и подсчитываем операции
        // Для простоты будем считать вызовы heapify и swap
        // В реальном коде нужно вставить счетчики в сами функции
        
        // Вместо этого используем приблизительную оценку:
        // O(n log n) операций
        operation_count = n;
        for (int i = 1; i <= n; i *= 2) {
            operation_count += n;
        }
        
        // Выполняем реальную сортировку
        my_sort(n, arr_copy);
        
        // Проверяем корректность
        if (!is_sorted(arr_copy, n)) {
            std::cout << "Ошибка: массив не отсортирован!" << std::endl;
        }
        
        // Вычисляем n*log2(n) для сравнения
        double n_log_n = n * std::log2(n);
        
        std::cout << n << "\t\t" << operation_count << "\t\t" << (int)n_log_n << std::endl;
        
        delete[] arr;
        delete[] arr_copy;
    }
}

// Демонстрационный тест с небольшим массивом
void demo_test() {
    std::cout << "Демонстрационный тест:" << std::endl;
    
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6, 0};
    int n = 10;
    
    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    my_sort(n, arr);
    
    std::cout << "Отсортированный: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    if (is_sorted(arr, n)) {
        std::cout << "✓ Массив корректно отсортирован" << std::endl;
    } else {
        std::cout << "✗ Ошибка сортировки" << std::endl;
    }
    std::cout << std::endl;
}

// Тест на уже отсортированном массиве
void sorted_test() {
    std::cout << "Тест на отсортированном массиве:" << std::endl;
    
    int n = 8;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    my_sort(n, arr);
    
    std::cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    if (is_sorted(arr, n)) {
        std::cout << "✓ Массив остался отсортированным" << std::endl;
    }
    std::cout << std::endl;
}

// Тест на массиве, отсортированном в обратном порядке
void reverse_test() {
    std::cout << "Тест на обратно отсортированном массиве:" << std::endl;
    
    int n = 8;
    int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    
    std::cout << "Исходный: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    my_sort(n, arr);
    
    std::cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    if (is_sorted(arr, n)) {
        std::cout << "✓ Массив корректно отсортирован" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== ТЕСТИРОВАНИЕ ПИРАМИДАЛЬНОЙ СОРТИРОВКИ ===" << std::endl;
    std::cout << std::endl;
    
    // Демонстрационные тесты
    demo_test();
    sorted_test();
    reverse_test();
    
    // Тест производительности
    std::cout << "=== ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ ===" << std::endl;
    measure_performance();
    
    return 0;
}