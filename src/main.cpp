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
using namespace std;

int main(int argc, const char **argv)
{ 
    cout << "args: " << endl;
    for (auto i = 1; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl << endl;

    ArgParser parser;

    EmptyArg help('h', "help", "Get some help");
    EmptyArg fast('f', "fast", "Gotta go fast (ex. -f)");
    EmptyArg sleep('s', "sleep");
    EmptyArg megafast('m', "megafast", "Gotta go megafast");
    BoolArg lock('l', "lock", "Input 0 or 1 (ex. -l=0)");
    IntArg warnings('w', "warnings", "Input integer value (ex. -w=10)");
    StringArg name('n', "name", "Input string value (ex. -n=o.txt)");
    MultiStringArg output('o', "output");
    MultiIntArg codes('c', "codes");
    MultiBoolArg authorizes('a', "authorizes");

    parser.Add(&help);
    parser.Add(&fast);
    parser.Add(&sleep);
    parser.Add(&megafast);
    parser.Add(&lock);
    parser.Add(&warnings);
    parser.Add(&name);
    parser.Add(&output);
    parser.Add(&codes);
    parser.Add(&authorizes);

    cout << "Try to parse: ";
    if (parser.Parse(argc, argv)) {
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
        cout << "False" << endl;

    return 0;
}