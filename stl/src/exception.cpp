//
// Created by Glavo on 17-9-30.
//

#include <exception>
using namespace std;

static unexpected_handler handler = nullptr;

char const *std::exception::what() const noexcept {
    return "std::exception";
}

char const *std::bad_exception::what() const noexcept {
    return "std::bad_exception";
}
