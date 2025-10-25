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
    std::cin >> f.signed_val;//можно взять 7

    std::cout << "int: " << f.signed_val << std::endl;
    intToBit(f.signed_val);
    std::cout << "unsigned: " << f.unsigned_val << std::endl;
    intToBit(f.signed_val);
    return 0;
}