//
// Created by Glavo on 17-9-29.
//

#include <cmath>
#include <stdlib.h>
#include <initializer_list>

class C {
    char const *data;
public:
    C(std::initializer_list<char> il) {
        auto *c = static_cast<char *>(malloc(sizeof(char) * il.size()));
        data = c;

        for (auto ch : il) {
            *c++ = ch;
        }
    }

};

int main() {
    C c = {
            'a', 'b', 'c', 'd'
    };
}

