//число = (-1)^знак × 1.мантисса × 2^(экспонента-127)
#include <iostream>

union FloatUnion {
    float float_val;
    unsigned int int_val;
};

void intToBit(int a){
    for (int i = 8*sizeof(int) - 1; i >= 0;i--){
        std::cout << ((a >> i) & 1);
    }
}

void FloatToBin(float f) {
    FloatUnion u;
    u.float_val = f;
    unsigned int bits = u.int_val;// по памяти приравниваем флоат к инту, чтобы проделать то же, что с интами из первого пункта лабы
    
    unsigned int sign = (bits >> 31) & 1; // знак (только 1 бит)
    unsigned int exponent = (bits >> 23) & 0xFF; // экспонента (только 8 младших бит)
    unsigned int mantissa = bits & 0x7FFFFF; // мантисса (только 23 младших бита)
    
    std::cout << "Число: " << f << std::endl;
    std::cout << "Формула перевода: число = (-1)^знак * 1.мантисса * 2^(экспонента-127)" << std::endl; 
    std::cout << "Двоичная форма: ";
    
    // Выводим все 32 бита вручную
    for (int i = 31; i >= 0; i--) {
        std::cout << ((bits >> i) & 1);
        if (i == 31 || i == 23){
            std::cout << " "; // Разделяем знак, экспоненту, мантиссу
        }
    }
    
    std::cout << std::endl;
    std::cout << "Знак: " << sign << std::endl;
    std::cout << "Экспонента: " << exponent << " (exp - 127 = " << (int)(exponent - 127) << ")" << std::endl;
    std::cout << "Мантисса: ";
    intToBit(mantissa); 
}

int main() {
    float f;
    f = -3.5f;
    FloatToBin(f);
    return 0;
}