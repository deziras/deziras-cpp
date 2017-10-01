//
// Created by Glavo on 17-9-29.
//

#include<cmath>
#include <stdlib.h>
#include <initializer_list>
#include <cstdio>
#include <exception>

class C {
    char const *data;
public:
    C(std::initializer_list<char> il) {
        auto *c = (char *) malloc(sizeof(char) * il.size());
        data = c;

        for (auto ch : il) {
            *c++ = ch;
        }
    }

};

int main() {
    auto x = {1, 2, 3};
    auto b = C{'a', 'b', 'c'};

    throw std::exception();
}

