template<typename T>
class subforwardlist {
    struct Node {
        T data;
        Node* next;
        
        Node(const T& d) : data(d), next(nullptr) {}
        Node(T&& d) : data(std::move(d)), next(nullptr) {}
    };

    Node* begin;

public:
    // Конструктор по умолчанию
    subforwardlist() : begin(nullptr) {}
    
    // Деструктор
    ~subforwardlist() {
        clear();
    }
    
    // Конструктор копирования
    subforwardlist(const subforwardlist& other) : begin(nullptr) {
        if (other.begin) {
            Node* other_current = other.begin;
            Node** current_ptr = &begin;
            
            while (other_current) {
                *current_ptr = new Node(other_current->data);
                current_ptr = &((*current_ptr)->next);
                other_current = other_current->next;
            }
        }
    }
    
    // Конструктор перемещения
    subforwardlist(subforwardlist&& other) : begin(other.begin) {
        other.begin = nullptr;
    }
    
    // Оператор присваивания (копирование)
    subforwardlist& operator=(const subforwardlist& other) {
        if (this != &other) {
            clear();
            
            if (other.begin) {
                Node* other_current = other.begin;
                Node** current_ptr = &begin;
                
                while (other_current) {
                    *current_ptr = new Node(other_current->data);
                    current_ptr = &((*current_ptr)->next);
                    other_current = other_current->next;
                }
            }
        }
        return *this;
    }
    
    // Оператор присваивания (перемещение)
    subforwardlist& operator=(subforwardlist&& other) {
        if (this != &other) {
            clear();
            begin = other.begin;
            other.begin = nullptr;
        }
        return *this;
    }

    // добавление элемента в конец
    void push_back(const T& data) {
        Node* new_node = new Node(data);
        
        if (!begin) {
            begin = new_node;
            return;
        }
        
        Node* current = begin;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }

    // удаление элемента с конца
    T pop_back() {
        if (!begin) return T{};
        
        if (!begin->next) {
            T data = begin->data;
            delete begin;
            begin = nullptr;
            return data;
        }
        
        Node* current = begin;
        while (current->next->next) {
            current = current->next;
        }
        
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        return data;
    }

    // добавление элемента в начало
    void push_forward(const T& data) {
        Node* new_node = new Node(data);
        new_node->next = begin;
        begin = new_node;
    }

    // удаление элемента из начала
    T pop_forward() {
        if (!begin) return T{};
        
        T data = begin->data;
        Node* temp = begin;
        begin = begin->next;
        delete temp;
        return data;
    }

    // добавление элемента с порядковым номером where
    void push_where(unsigned int where, const T& data) {
        if (where == 0) {
            push_forward(data);
            return;
        }
        
        Node* current = begin;
        for (unsigned int i = 0; i < where - 1 && current; i++) {
            current = current->next;
        }
        
        if (!current) {
            push_back(data);
            return;
        }
        
        Node* new_node = new Node(data);
        new_node->next = current->next;
        current->next = new_node;
    }

    // удаление элемента с порядковым номером where
    T erase_where(unsigned int where) {
        if (!begin) return T{};
        
        if (where == 0) {
            return pop_forward();
        }
        
        Node* current = begin;
        for (unsigned int i = 0; i < where - 1 && current->next; i++) {
            current = current->next;
        }
        
        if (!current->next) return T{};
        
        Node* temp = current->next;
        T data = temp->data;
        current->next = temp->next;
        delete temp;
        return data;
    }

    // определение размера
    unsigned int size() {
        unsigned int count = 0;
        Node* current = begin;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

private:
    // Вспомогательный метод для очистки списка
    void clear() {
        while (begin) {
            Node* temp = begin;
            begin = begin->next;
            delete temp;
        }
    }
};