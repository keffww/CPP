#include <iostream>
int main(){
    float a = 0.000000000000001f;
    float b = 0.000000000000002f;
    float c = 0.000000000000003f;
    if (a + b == c){
        std::cout << "равно";
    }
    else {
        std::cout << "не равно";
    }
    std::cout << std::endl;
    float d = 1.0e8f;
    float e = 1.0f;
    float f = -1.0e8f;
    if ((e + d) + f == e + (d + f)){
        std::cout << "ассоц";
    }
    else {
        std::cout << "не ассоц";
    }
    //Короче, из-за округлений может чё-то где-то потеряться. Так что не особо приемлемая тема так сравнивать.
    //Без арифм операций сравнение безопаснор
}