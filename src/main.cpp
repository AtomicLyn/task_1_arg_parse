#include <iostream>
#include "Args.hpp"
#include "ArgParser.hpp"
#include "Validators.hpp"

using namespace args_parse;
using std::cout;
using std::endl;
using std::boolalpha;

int main(int argc, const char **argv)
{ 
    cout << "args: " << endl;
    for (auto i = 1; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl << endl;


    ArgParser parser;
    EmptyArg help{ 'h', "help", "Get some help" };
    EmptyArg fast{ 'f', "fast", "Gotta go fast (ex. -f)" };
    EmptyArg sleep{ 's', "sleep" };
    EmptyArg megafast{ 'm', "megafast", "Gotta go megafast" };
    BoolArg lock{ 'l', "lock", "Input 0 or 1 (ex. -l=0)" };

    IntInRangeValidator warnasValidator{ 0, 100 };
    IntArg warnas{ std::make_unique<IntInRangeValidator>(warnasValidator), 'w', "warnas", "Input integer value (ex. -w=10)" };

    IntInRangeValidator warningsValidator{ 0,100 };
    IntArg warnings{ std::make_unique<IntInRangeValidator>(warningsValidator), 'W', "warnings", "Input integer value (ex. -W=10)"};

    StringFileNameValidator nameValidator{};
    StringArg name{ std::make_unique<StringFileNameValidator>(nameValidator), 'n', "name", "Input string value (ex. -n=o.txt)" };

    MultiBoolArg authorizes{ 'a', "authorizes" };

    IntInRangeValidator codesValidator{ 0, 1000 };
    MultiIntArg codes{ std::make_unique<IntInRangeValidator>(IntInRangeValidator{0, 100}), 'c', "codes" };

    StringFileFormatValidator outputValidator{};
    MultiStringArg output{ std::make_unique<StringFileFormatValidator>(outputValidator), 'o', "output" };

    parser.Add(&help);
    parser.Add(&fast);
    parser.Add(&sleep);
    parser.Add(&megafast);
    parser.Add(&lock);
    parser.Add(&warnings);
    parser.Add(&warnas);
    parser.Add(&name);
    parser.Add(&output);
    parser.Add(&codes);
    parser.Add(&authorizes);

    cout << "Try to parse: " << std::endl;
    const auto result = parser.Parse(argc, argv);
    if (result.IsOk()) {
        cout << "True" << endl << endl;

        if (help.IsDefined()) {
            cout << parser.GetHelp() << endl;
        }

        cout << "Arguments:" << endl;

        if (fast.IsDefined()) {
            cout << "Empty argument: " << fast.GetOption() << "/" << fast.GetLongOption() << " " << endl;
        }
        if (sleep.IsDefined()) {
            cout << "Empty argument: " << sleep.GetOption() << "/" << sleep.GetLongOption() << " " << endl;
        }
        if (megafast.IsDefined()) {
            cout << "Empty argument: " << megafast.GetOption() << "/" << megafast.GetLongOption() << " " << endl;
        }
        if (lock.IsDefined()) {
            cout << "Bool argument: " << boolalpha << lock.GetOption() << "/" << lock.GetLongOption() << " " << lock.GetValue() << endl;
        }
        if (warnings.IsDefined()) {
            cout << "Int argument: " << warnings.GetOption() << "/" << warnings.GetLongOption() << " " << warnings.GetValue() << endl;
        }
        if (warnas.IsDefined()) {
            cout << "Int argument: " << warnas.GetOption() << "/" << warnas.GetLongOption() << " " << warnas.GetValue() << endl;
        }
        if (name.IsDefined()) {
            cout << "String argument: " << name.GetOption() << "/" << name.GetLongOption() << " " << name.GetValue() << endl;
        }
        if (output.IsDefined()) {
            cout << "MultiString argument: " << output.GetOption() << "/" << output.GetLongOption() << " ";
            for (auto value : output.GetValues()) {
                cout << value << ", ";
            }
            cout << endl;
        }
        if (codes.IsDefined()) {
            cout << "MultiInt argument: " << codes.GetOption() << "/" << codes.GetLongOption() << " ";
            for (auto value : codes.GetValues()) {
                cout << value << ", ";
            }
            cout << endl;
        }
        if (authorizes.IsDefined()) {
            cout << "MultiBool argument: " << authorizes.GetOption() << "/" << authorizes.GetLongOption() << " ";
            for (auto value : authorizes.GetValues()) {
                cout << value << ", ";
            }
            cout << endl;
        }
    }
    else
        cout << result.GetError().Message << endl;

    return 0;
}