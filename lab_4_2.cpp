struct list {
    int data;              // значение элемента
    list* next;  // указатель на следующий элемент
};

bool init(list **sfl) {
    *sfl = nullptr;
    return true;
}

bool push_back(list **sfl, int d) {
    list *new_node = new list;
    new_node->data = d;
    new_node->next = nullptr;
    if (*sfl == nullptr) {
        *sfl = new_node;
        return true;
    }
    list *current = *sfl;
    while (current->next != nullptr) {
        current = current->next;
    }
    
    current->next = new_node;
    return true;
}

int pop_back(list **sfl) {
    if (*sfl == nullptr) return 0;  // список пуст
    
    if ((*sfl)->next == nullptr) {
        int data = (*sfl)->data;
        delete *sfl;
        *sfl = nullptr;
        return data;
    }
    
    list *current = *sfl;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    int data = current->next->data;
    delete current->next;
    current->next = nullptr;
    return data;
}
bool push_forward(list **sfl, int d) {
    list *new_node = new list;
    new_node->data = d;
    new_node->next = *sfl;  // новый элемент указывает на старый первый
    *sfl = new_node;        // новый элемент становится первым
    return true;
}

// Удаляем первый элемент
int pop_forward(list **sfl) {
    if (*sfl == nullptr) return 0;  // список пуст
    
    int data = (*sfl)->data;   
    list *temp = *sfl; 
    *sfl = (*sfl)->next;      
    delete temp;             
    return data;
}

// Добавляем элемент на определенную позицию
bool push_where(list **sfl, unsigned int where, int d) {
    if (where == 0) {
        return push_forward(sfl, d);
    }
    
    list *current = *sfl;
    for (unsigned int i = 0; i < where - 1 && current != nullptr; i++) {
        current = current->next;
    }
    
    if (current == nullptr) {
        return push_back(sfl, d);
    }
    
    // Вставляем между current и current->next
    list *new_node = new list;
    new_node->data = d;
    new_node->next = current->next;
    current->next = new_node;
    return true;
}

// Удаляем элемент с определенной позиции
int erase_where(list **sfl, unsigned int where) {
    if (*sfl == nullptr) return 0; 
    
    if (where == 0) {
        return pop_forward(sfl);
    }
    // Ищем элемент ПЕРЕД тем, который нужно удалить
    list *current = *sfl;
    for (unsigned int i = 0; i < where - 1 && current->next != nullptr; i++) {
        current = current->next;
    }
    
    // Удаляем элемент
    list *temp = current->next;
    int data = temp->data;
    current->next = temp->next;
    delete temp;
    return data;
}

// Считаем количество элементов
unsigned int size(list *sfl) {
    unsigned int count = 0;
    while (sfl != nullptr) {
        count++;
        sfl = sfl->next;
    }
    return count;
}

// Очищаем весь список
void clear(list **sfl) {
    while (*sfl != nullptr) {
        list *temp = *sfl;
        *sfl = (*sfl)->next;     
        delete temp;                 
    }
}