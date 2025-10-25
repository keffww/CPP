#include <iostream>

int main() {
    float sum = 0.0f;
    int k = 1;
    
    std::cout << "Поиск k, при котором 1/k перестает увеличивать сумму:" << std::endl;
    
    while (true) {
        float new_sum = sum + 1.0f / k;
        if (new_sum == sum) {
            std::cout << "Найдено k = " << k << std::endl;
            std::cout << "Сумма до этого момента: " << sum << std::endl;
            break;
        }
        sum = new_sum;
        k++;
    }
    
    //сумма до n = k + 100 прямым способом
    int n = k + 100;
    float sum_forward = 0.0f;
    
    std::cout << "Прямое суммирование от 1 до " << n << ":" << std::endl;
    for (int i = 1; i <= n; i++) {
        sum_forward += 1.0f / i;
    }
    std::cout << "Прямая сумма = " << sum_forward << std::endl;
    
    //сумма обратным способом
    float sum_backward = 0.0f;
    
    std::cout << "Обратное суммирование от " << n << " до 1:" << std::endl;
    for (int i = n; i >= 1; i--) {
        sum_backward += 1.0f / i;
    }
    std::cout << "Обратная сумма = " << sum_backward << std::endl;
    
    // Шаг 4: Сравнение результатов
    std::cout << "Сравнение результатов:" << std::endl;
    std::cout << "Разница: " << std::scientific << std::abs(sum_forward - sum_backward) << std::endl;
    std::cout << "Прямая сумма = " << sum_forward << " != " <<  "Обратная сумма = " << sum_backward << std::endl;
    
    return 0;
}

/* 
Эффект объясняется тем, что (a + b) + c != a + (b + c). Типа важен порядок
Если сначала складывать большие числа с всё более и более маленькими, то округление начнётся гораздо быстрее,
Чем если бы мы посчитали бы сумму самых маленьких а потом её бы сложили с большими числами.
*/