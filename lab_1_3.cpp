#include <iostream>

union IntUnion {
    int signed_val;
    unsigned int unsigned_val;
};

void intToBit(unsigned int value) {
    for (int i = 8*sizeof(int) - 1; i >= 0;i--) {
        std::cout << ((value >> i) & 1);
    }
    std::cout << std::endl;
}

int main() {
    IntUnion f;
  /*std::cin >> f.signed_val;//можно взять 7

    std::cout << "int: " << f.signed_val << std::endl;
    intToBit(f.signed_val);
    std::cout << "unsigned: " << f.unsigned_val << std::endl;
    intToBit(f.signed_val);
    */

    f.unsigned_val = 0;
    std::cout << "0 (unsigned) = " << f.unsigned_val << std::endl;
    std::cout << "Биты: ";
    intToBit(f.unsigned_val);
    std::cout << std::endl;

    f.unsigned_val = 0 - 1;  // Переполнение!
    std::cout << "0 - 1 (unsigned) = " << f.unsigned_val << std::endl;
    std::cout << "Биты: ";
    intToBit(f.unsigned_val);
    std::cout << std::endl;
    //Типа в дефолтной логике человека 0-1=-1, а не 0-1=4294967295
    return 0;
}