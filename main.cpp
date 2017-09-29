//
// Created by Glavo on 17-9-29.
//

#include <cmath>
#include <stdlib.h>
#include <initializer_list>
#include <stdio.h>
#include <new>

class C {
public:
    ~C() {
        printf("delete!");
    }
};

int main() {
    auto p = new (std::nothrow) C;
    delete p;
}

