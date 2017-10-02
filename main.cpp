//
// Created by Glavo on 17-9-29.
//

#include <initializer_list>
#include <cstdlib>
#include <typeinfo>
#include <cstdio>

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
    printf("%s",  typeid(C).name());
}

