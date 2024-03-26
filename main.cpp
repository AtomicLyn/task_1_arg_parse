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

    EmptyArg emptyCheck('f', "fast", "instructing the parser to work faster (it tries very hard)");
    BoolArg boolCheck('l', "lock", "closes the user's access to the argument value (joke, it doesn't work anyway)");
    IntArg intCheck('w', "warnings", "warns the user about sudden errors during parsing(did you believe it ? )");
    StringArg stringCheck('o', "output", "specifying a file for output values");

    parser.Add(&emptyCheck);
    parser.Add(&boolCheck);
    parser.Add(&intCheck);
    parser.Add(&stringCheck);

    if (parser.TryParse(argc, argv)) {
        std::cout << "Try to parse: true";
        for (auto argument : parser.GetArguments()) {
            std::cout << argument->GetDescription() << std::endl;
        }
    }

    
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