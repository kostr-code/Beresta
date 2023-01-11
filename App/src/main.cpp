#include <iostream>
#include "../include/main.h"

int main(int, char**) {
    std::cout << max(10, 15) << std::endl;
}

int max(int a, int b){
    return a>b ? a : b;
}