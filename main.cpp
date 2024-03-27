#include <iostream>
#include "EmptyArg.hpp"
#include "BoolArg.hpp"
#include "IntArg.hpp"
#include "StringArg.hpp"
#include "ArgParser.hpp"

using namespace args_parse;

int main(int argc, const char **argv)
{ 
    std::cout << "args: " << std::endl;
    for (auto i = 1; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl << std::endl;

    ArgParser parser;

    EmptyArg fast('f', "fast");
    EmptyArg sleep('s', "sleep");
    EmptyArg megafast('m', "megafast");
    BoolArg lock('l', "lock");
    IntArg warnings('w', "warnings");
    StringArg output('o', "output");

    parser.Add(&fast);
    parser.Add(&sleep);
    parser.Add(&megafast);
    parser.Add(&lock);
    parser.Add(&warnings);
    parser.Add(&output);

    if (parser.Parse(argc, argv)) {
        std::cout << "Try to parse: True" << std::endl << std::endl;
        std::cout << "Arguments:" << std::endl;
        if (fast.IsDefined()) {
            std::cout << "Empty argument: " << fast.GetOption() << "/" << fast.GetLongOption() << " " << std::endl;
        }
        if (sleep.IsDefined()) {
            std::cout << "Empty argument: " << sleep.GetOption() << "/" << sleep.GetLongOption() << " " << std::endl;
        }
        if (megafast.IsDefined()) {
            std::cout << "Empty argument: " << megafast.GetOption() << "/" << megafast.GetLongOption() << " " << std::endl;
        }
        if (lock.IsDefined()) {
            std::cout << "Bool argument: " << std::boolalpha << lock.GetOption() << "/" << lock.GetLongOption() << " " << lock.GetValue() << std::endl;
        }
        if (warnings.IsDefined()) {
            std::cout << "Int argument: " << warnings.GetOption() << "/" << warnings.GetLongOption() << " " << warnings.GetValue() << std::endl;
        }
        if (output.IsDefined()) {
            std::cout << "String argument: " << output.GetOption() << "/" << output.GetLongOption() << " " << output.GetValue() << std::endl;
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