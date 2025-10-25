struct vector {
    int *mas;           // указатель на массив с данными
    unsigned int top;    // количество элементов в векторе
    unsigned int capacity; // общий размер выделенной памяти
};

// Создаем пустой вектор
bool init(vector *qv) {
    qv->mas = nullptr;  
    qv->top = 0;       
    qv->capacity = 0; 
    return true;
}

bool push_back(vector *qv, int d) {
    // Если места нет, увеличиваем память
    if (qv->top == qv->capacity) {
        unsigned int new_cap = (qv->capacity == 0) ? 2 : qv->capacity * 2;
        if (!resize(qv, new_cap)) return false;
    }
    
    qv->mas[qv->top] = d;  
    qv->top++;         
    return true;
}

int pop_back(vector *qv) {
    if (qv->top == 0) return 0;  // если вектор пуст
    qv->top--;                 
    return qv->mas[qv->top];    
}

// Изменяем размер памяти
bool resize(vector *qv, unsigned int new_capacity) {
    int *new_mas = new int[new_capacity];
    unsigned int copy_count = (qv->top < new_capacity) ? qv->top : new_capacity;
    for (unsigned int i = 0; i < copy_count; i++) {
        new_mas[i] = qv->mas[i];
    }
    delete[] qv->mas;  // освобождаем старую память
    qv->mas = new_mas; // используем новую память
    qv->top = copy_count;
    qv->capacity = new_capacity;
    return true;
}

// Убираем лишнюю память
void shrink_to_fit(vector *qv) {
    if (qv->top < qv->capacity) {
        resize(qv, qv->top);  // меняем размер на точное количество элементов
    }
}

// Очищаем содержимое (память остается)
void clear(vector *qv) {
    qv->top = 0;  
}

// Полностью уничтожаем вектор
void destructor(vector *qv) {
    delete[] qv->mas; 
    init(qv);     
}