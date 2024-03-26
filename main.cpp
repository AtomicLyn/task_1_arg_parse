#include <iostream>
#include "EmptyArg.hpp"

using namespace args_parse;

int main(int argc, const char **argv)
{
    std::cout << "quantity: " << argc << std::endl;
    std::cout << "args: " << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    EmptyArg check("-c", "--check");
    for (auto i = 1; i < argc; i++) {
        std::cout << std::boolalpha << check.TryParse(argv[i]) << std::endl;
    }
}