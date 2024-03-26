#include <iostream>
#include "EmptyArg.hpp"
#include "BoolArg.hpp"
#include "IntArg.hpp"
#include "StringArg.hpp"
#include "ArgParser.hpp"

using namespace args_parse;

int main(int argc, const char **argv)
{ 
    std::cout << "quantity: " << argc << std::endl;
    std::cout << "args: " << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;

    ArgParser parser;

    EmptyArg emptyCheck('f', "fast");
    BoolArg boolCheck('l', "lock");
    IntArg intCheck('w', "warnings");
    StringArg stringCheck('o', "output");

    parser.Add(&emptyCheck);
    parser.Add(&boolCheck);
    parser.Add(&intCheck);
    parser.Add(&stringCheck);

    if (parser.TryParse(argc, argv)) {
        std::cout << "Try to parse: True" << std::endl;
        std::cout << "Arguments:" << std::endl;
        for (auto argument : parser.GetArguments()) {
            switch (argument->GetType()) {
            case ArgumentType::Empty:
                std::cout << "Empty argument" << std::endl;
                break;
            case ArgumentType::Bool:
                std::cout << "Bool argument: " << std::boolalpha << ((BoolArg*)argument)->GetValue() << std::endl;
                break;
            case ArgumentType::Int:
                std::cout << "Int argument: " << ((IntArg*)argument)->GetValue() << std::endl;
                break;
            case ArgumentType::String:
                std::cout << "String argument: " << ((StringArg*)argument)->GetValue() << std::endl;
                break;
            default:
                std::cout << "Undefined argument!" << std::endl;
            }
        }
    }
    else
        std::cout << "Try to parse: False" << std::endl;

    
    /*EmptyArg emptyCheck('c', "check");
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
    std::cout << std::endl;*/
}