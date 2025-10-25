#include <iostream>

union IntUnion {
    int signed_val;
    unsigned int unsigned_val;
};

void intToBit(int a){
    for (int i = 8*sizeof(int) - 1; i >= 0;i--){
        std::cout << ((a >> i) & 1);
    }
}
int main (){
    IntUnion f;
    std::cin >> f.signed_val;
    intToBit(f.signed_val);
    return 0;
}