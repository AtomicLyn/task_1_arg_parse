#include <iostream>
#include "EmptyArg.hpp"
#include "BoolArg.hpp"
#include "IntArg.hpp"
#include "StringArg.hpp"

using namespace args_parse;

int main(int argc, const char **argv)
{ 
    std::cout << "quantity: " << argc << std::endl;
    std::cout << "args: " << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << "[" << i << "] - " << argv[i] << std::endl;
    }
    std::cout << std::endl;

    
    EmptyArg emptyCheck('c', "check");
    std::cout << "EmptyCheck:" << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << "[" << i << "] - " << std::boolalpha << emptyCheck.TryParse(argv[i]) << std::endl;
    }
    std::cout << std::endl;

    BoolArg boolCheck('c', "check");
    std::cout << "BoolCheck:" << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << "[" << i << "] - " << std::boolalpha << boolCheck.TryParse(argv[i]) << std::endl;
    }
    std::cout << std::endl;

    IntArg intCheck('c', "check");
    std::cout << "IntCheck:" << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << "[" << i << "] - " << std::boolalpha << intCheck.TryParse(argv[i]) << std::endl;
    }
    std::cout << std::endl;

    StringArg stringCheck('c', "check");
    std::cout << "StringCheck:" << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << "[" << i << "] - " << std::boolalpha << stringCheck.TryParse(argv[i]) << std::endl;
    }
    std::cout << std::endl;
}