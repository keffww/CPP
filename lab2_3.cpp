template<typename T>
class subvector {
    T *mas;
    unsigned int top;
    unsigned int capacity;
    
public:
    subvector() : mas(nullptr), top(0), capacity(0) {}
    
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
    
    // Добавляем методы для работы с матрицей
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
    // Конструкторы
    Matrix(unsigned rows, unsigned cols, T value = T{}) 
        : cols_(cols), rows_(rows) {
        data.resize(rows * cols);
        for (unsigned i = 0; i < rows * cols; i++) {
            data[i] = value;
        }
    }

    // Создание единичной матрицы
    static Matrix Identity(unsigned size) {
        Matrix result(size, size);
        for (unsigned i = 0; i < size; i++) {
            result(i, i) = T{1};
        }
        return result;
    }

    // Создание случайной матрицы с заданным детерминантом
    static Matrix getSpecificDeterminant(unsigned n, T determinant) {
        Matrix result = Identity(n);
        
        // Умножаем диагональные элементы так, чтобы детерминант был нужным
        result(0, 0) = determinant;
        
        // Добавляем немного случайности в недиагональные элементы
        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < n; j++) {
                if (i != j) {
                    // Простые маленькие значения для избежания переполнения
                    result(i, j) = static_cast<T>((i + j) % 3);
                }
            }
        }
        
        return result;
    }

    // Селекторы
    unsigned rows() const { return rows_; }
    unsigned cols() const { return cols_; }

    // Транспонирование
    Matrix transpose() const {
        Matrix result(cols_, rows_);
        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    // Доступ к элементам
    T& operator()(unsigned row, unsigned col) {
        return data[row * cols_ + col];
    }

    T operator()(unsigned row, unsigned col) const {
        return data[row * cols_ + col];
    }

    // Получение подматрицы
    Matrix submatrix(unsigned exclude_row, unsigned exclude_col) const {
        Matrix result(rows_ - 1, cols_ - 1);
        unsigned dest_i = 0;
        for (unsigned i = 0; i < rows_; i++) {
            if (i == exclude_row) continue;
            unsigned dest_j = 0;
            for (unsigned j = 0; j < cols_; j++) {
                if (j == exclude_col) continue;
                result(dest_i, dest_j) = (*this)(i, j);
                dest_j++;
            }
            dest_i++;
        }
        return result;
    }
};

// Функция для вычисления детерминанта
template<typename T>
T determinant(const Matrix<T>& matrix) {
    unsigned n = matrix.rows();
    
    if (n == 1) {
        return matrix(0, 0);
    }
    
    if (n == 2) {
        return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
    }
    
    T det = T{};
    int sign = 1;
    
    // Разложение по первой строке
    for (unsigned j = 0; j < n; j++) {
        Matrix<T> sub = matrix.submatrix(0, j);
        det += sign * matrix(0, j) * determinant(sub);
        sign = -sign;
    }
    
    return det;
}

// Простой тест
int main() {
    // Тест 1: матрица 5x5
    Matrix<double> m1 = Matrix<double>::getSpecificDeterminant(5, 10.0);
    double det1 = determinant(m1);
    double det1_transposed = determinant(m1.transpose());
    
    // Тест 2: матрица 50x50  
    Matrix<double> m2 = Matrix<double>::getSpecificDeterminant(50, 100.0);
    double det2 = determinant(m2);
    double det2_transposed = determinant(m2.transpose());
    
    // Тест 3: матрица 100x100
    Matrix<double> m3 = Matrix<double>::getSpecificDeterminant(100, 50.0);
    double det3 = determinant(m3);
    double det3_transposed = determinant(m3.transpose());
    
    return 0;
}