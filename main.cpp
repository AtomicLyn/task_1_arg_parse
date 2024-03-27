#include <iostream>
#include "EmptyArg.hpp"
#include "BoolArg.hpp"
#include "IntArg.hpp"
#include "StringArg.hpp"
#include "MultiBoolArg.hpp"
#include "MultiIntArg.hpp"
#include "MultiStringArg.hpp"
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

    EmptyArg help('h', "help");
    EmptyArg fast('f', "fast");
    EmptyArg sleep('s', "sleep");
    EmptyArg megafast('m', "megafast");
    BoolArg lock('l', "lock");
    IntArg warnings('w', "warnings");
    StringArg name('n', "name");
    MultiStringArg output('o', "output");

    parser.Add(&help);
    parser.Add(&fast);
    parser.Add(&sleep);
    parser.Add(&megafast);
    parser.Add(&lock);
    parser.Add(&warnings);
    parser.Add(&name);
    parser.Add(&output);

    std::cout << "Try to parse: ";
    if (parser.Parse(argc, argv)) {
        std::cout << "True" << std::endl << std::endl;

        if (help.IsDefined()) {
            std::cout << parser.GetHelp() << std::endl;
        }

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
        if (name.IsDefined()) {
            std::cout << "String argument: " << name.GetOption() << "/" << name.GetLongOption() << " " << name.GetValue() << std::endl;
        }
        if (output.IsDefined()) {
            std::cout << "String argument: " << output.GetOption() << "/" << output.GetLongOption() << " ";
            for (auto value : output.GetValues()) {
                std::cout << value << ", ";
            }
            std::cout << std::endl;
        }
    }
    else
        std::cout << "False" << std::endl;

    return 0;
}