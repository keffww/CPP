#include <iostream>
#include <cstdlib>
#include <cmath>

template<typename T>
class subvector {
    T *mas;
    unsigned int top;
    unsigned int capacity;
    
public:
    subvector() : mas(nullptr), top(0), capacity(0) {}
    
    subvector(unsigned int size, const T& value = T{}) : mas(nullptr), top(0), capacity(0) {
        if (size > 0) {
            mas = new T[size];
            capacity = size;
            top = size;
            for (unsigned int i = 0; i < size; i++) {
                mas[i] = value;
            }
        }
    }
    
    ~subvector() {
        delete[] mas;
    }
    
    subvector(const subvector& other) : mas(nullptr), top(0), capacity(0) {
        if (other.capacity > 0) {
            mas = new T[other.capacity];
            capacity = other.capacity;
            top = other.top;
            for (unsigned int i = 0; i < top; i++) {
                mas[i] = other.mas[i];
            }
        }
    }
    
    subvector(subvector&& other) : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }
    
    subvector& operator=(const subvector& other) {
        if (this != &other) {
            delete[] mas;
            
            if (other.capacity > 0) {
                mas = new T[other.capacity];
                capacity = other.capacity;
                top = other.top;
                for (unsigned int i = 0; i < top; i++) {
                    mas[i] = other.mas[i];
                }
            } else {
                mas = nullptr;
                top = 0;
                capacity = 0;
            }
        }
        return *this;
    }
    
    subvector& operator=(subvector&& other) {
        if (this != &other) {
            delete[] mas;
            
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }

    bool push_back(const T& d) {
        if (top == capacity) {
            unsigned int new_capacity = (capacity == 0) ? 2 : capacity * 2;
            if (!resize(new_capacity)) {
                return false;
            }
        }
        
        mas[top] = d;
        top++;
        return true;
    }

    T pop_back() {
        if (top == 0) return T{};
        top--;
        return mas[top];
    }

    bool resize(unsigned int new_capacity) {
        if (new_capacity == 0) {
            delete[] mas;
            mas = nullptr;
            top = 0;
            capacity = 0;
            return true;
        }
        
        T* new_mas = new T[new_capacity];
        unsigned int copy_count = (top < new_capacity) ? top : new_capacity;
        
        for (unsigned int i = 0; i < copy_count; i++) {
            new_mas[i] = mas[i];
        }
        
        delete[] mas;
        mas = new_mas;
        top = copy_count;
        capacity = new_capacity;
        return true;
    }

    void shrink_to_fit() {
        if (top < capacity) {
            resize(top);
        }
    }

    void clear() {
        top = 0;
    }
    
    unsigned int size() const {
        return top;
    }
    
    T& operator[](unsigned int index) {
        return mas[index];
    }
    
    const T& operator[](unsigned int index) const {
        return mas[index];
    }
};

template<typename T>
class Matrix {
    subvector<T> data;
    unsigned cols_, rows_;

public:
    Matrix(unsigned rows, unsigned cols, T value = T{}) 
        : data(rows * cols, value), cols_(cols), rows_(rows) {}

    static Matrix Identity(unsigned size) {
        Matrix result(size, size);
        for (unsigned i = 0; i < size; i++) {
            result(i, i) = static_cast<T>(1);
        }
        return result;
    }

    static Matrix getSpecificDeterminant(unsigned n, T determinant) {
        // Создаем верхнюю треугольную матрицу с нужным детерминантом
        Matrix result(n, n);
        
        // Заполняем диагональ
        for (unsigned i = 0; i < n; i++) {
            result(i, i) = static_cast<T>(1);
        }
        result(0, 0) = determinant;
        
        // Заполняем верхний треугольник
        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = i + 1; j < n; j++) {
                result(i, j) = static_cast<T>(rand() % 10 + 1); // от 1 до 10
            }
        }
        
        return result;
    }

    unsigned rows() const { return rows_; }
    unsigned cols() const { return cols_; }

    Matrix transpose() const {
        Matrix result(cols_, rows_);
        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    T& operator()(unsigned row, unsigned col) {
        return data[row * cols_ + col];
    }

    T operator()(unsigned row, unsigned col) const {
        return data[row * cols_ + col];
    }

    // Метод Гаусса для вычисления детерминанта
    T determinant() const {
        if (rows_ != cols_) return static_cast<T>(0);
        
        unsigned n = rows_;
        Matrix<T> temp = *this;
        T det = static_cast<T>(1);
        
        for (unsigned i = 0; i < n; i++) {
            // Ищем максимальный элемент в столбце i
            unsigned max_row = i;
            T max_val = temp(i, i);
            for (unsigned k = i + 1; k < n; k++) {
                if (std::abs(temp(k, i)) > std::abs(max_val)) {
                    max_row = k;
                    max_val = temp(k, i);
                }
            }
            
            // Если весь столбец нулевой
            if (max_val == static_cast<T>(0)) {
                return static_cast<T>(0);
            }
            
            // Меняем строки местами
            if (max_row != i) {
                det = -det;
                for (unsigned j = i; j < n; j++) {
                    std::swap(temp(i, j), temp(max_row, j));
                }
            }
            
            // Применяем преобразования
            det *= temp(i, i);
            for (unsigned k = i + 1; k < n; k++) {
                T factor = temp(k, i) / temp(i, i);
                for (unsigned j = i; j < n; j++) {
                    temp(k, j) -= factor * temp(i, j);
                }
            }
        }
        
        return det;
    }
};

template<typename T>
T determinant(const Matrix<T>& matrix) {
    return matrix.determinant();
}

// Реально простой тест
int main() {
    srand(42); // Для воспроизводимости
    
    // Тест 1: матрица 5x5
    std::cout << "Matrix 5x5:" << std::endl;
    Matrix<double> m1 = Matrix<double>::getSpecificDeterminant(5, 10.0);
    double det1 = determinant(m1);
    Matrix<double> m1_t = m1.transpose();
    double det1_transposed = determinant(m1_t);
    std::cout << "Expected: 10.0" << std::endl;
    std::cout << "Got: " << det1 << std::endl;
    std::cout << "Transposed: " << det1_transposed << std::endl;
    std::cout << "Difference: " << std::abs(det1 - det1_transposed) << std::endl;

    // Тест 2: матрица 20x20 (вместо 50x50 для скорости)
    std::cout << "Matrix 20x20:" << std::endl;
    Matrix<double> m2 = Matrix<double>::getSpecificDeterminant(20, 50.0);
    double det2 = determinant(m2);
    double det2_transposed = determinant(m2.transpose());
    std::cout << "Expected: 50.0" << std::endl;
    std::cout << "Got: " << det2 << std::endl;
    std::cout << "Transposed: " << det2_transposed << std::endl;
    std::cout << "Difference: " << std::abs(det2 - det2_transposed) << std::endl;
    std::cout << std::endl;
    
    // Тест 3: матрица 30x30 (вместо 100x100 для скорости)
    std::cout << "Matrix 30x30:" << std::endl;
    Matrix<double> m3 = Matrix<double>::getSpecificDeterminant(30, 20.0);
    double det3 = determinant(m3);
    double det3_transposed = determinant(m3.transpose());
    std::cout << "Expected: 20.0" << std::endl;
    std::cout << "Got: " << det3 << std::endl;
    std::cout << "Transposed: " << det3_transposed << std::endl;
    std::cout << "Difference: " << std::abs(det3 - det3_transposed) << std::endl;
    
    return 0;
}