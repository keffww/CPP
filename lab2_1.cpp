template<typename T>
class subvector {
    int *mas;
// В массиве должен быть правильный тип
    unsigned int top;
    unsigned int capacity;
    
public:
    subvector() : mas(nullptr), top(0), capacity(0) {}
    // Деструктор
    ~subvector() {
        delete[] mas;
    }
    // Конструктор копирования
    subvector(const subvector& other) : mas(nullptr), top(0), capacity(0) {  // Тут можно было делегрировать дефолтный конструктор, чтобы не переписывать код, но вообще см след коммент
        if (other.capacity > 0) {
            mas = new int[other.capacity];
            capacity = other.capacity;
            top = other.top;
            // 18 - 19 нужно через список инициализации сделать
            for (unsigned int i = 0; i < top; i++) {
                mas[i] = other.mas[i];
            }
        }
    }
    // Конструктор перемещения
    subvector(subvector&& other) : mas(other.mas), top(other.top), capacity(other.capacity) {  // вот так бы везде
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }
    // Оператор присваивания (копирование)
    subvector& operator=(const subvector& other) {
        if (this != &other) {
            delete[] mas;
            // код ниже похож на логику копирующего конструктора. с помощью copy&swap можно было переиспользовать имеющийся код
            if (other.capacity > 0) {
                mas = new int[other.capacity];
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
    
    // Оператор присваивания (перемещение)
    subvector& operator=(subvector&& other) {
        // Тут правильнее не удалять себя (это долго), а отдать свое состояние внутрь other, так как это move операция, то такое поведение корректно
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

    // добавление элемента в конец недовектора
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

    // удаление элемента с конца недовектора
    T pop_back() {
        if (top == 0) return T{};
        top--;
        return mas[top];
    }

    // увеличение емкости недовектора
    bool resize(unsigned int new_capacity) {
        if (new_capacity == 0) {
            delete[] mas;
            mas = nullptr;
            top = 0;
            capacity = 0;
            return true;
        }
        
        int* new_mas = new int[new_capacity];
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

    // очистить неиспользуемую память
    void shrink_to_fit() {
        if (top < capacity) {
            resize(top);
        }
    }

    // очистить содержимое недовектора
    void clear() {
        top = 0;
    }

};
