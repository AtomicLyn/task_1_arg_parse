#include <iostream>
#include "Args.hpp"
#include "ArgParser.hpp"
#include "Validators.hpp"

using namespace args_parse;
using std::cout;
using std::endl;
using std::boolalpha;

int main(int argc, const char** argv)
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
	SingleArg<bool> lock{ 'l', "lock", "Input 0 or 1 (ex. -l=0)" };

	InRangeValidator<int> warnasValidator{ 0, 100 };
	SingleArg<int> warnas{ warnasValidator, 'w', "warnas", "Input integer value (ex. -w=10)" };

	InRangeValidator warningsValidator{ 0,100 };
	SingleArg<int> warnings{ warningsValidator, 'W', "warnings", "Input integer value (ex. -W=10)" };

	InRangeValidator fractionValidator{ 0.f,10.f };
	SingleArg<float> fraction{ fractionValidator, 'F', "fraction" };

	FileNameValidator<std::string> nameValidator{};
	SingleArg<std::string> name{ nameValidator, 'n', "name", "Input string value (ex. -n=o.txt)" };

	MultiArg<bool> authorizes{ 'a', "authorizes" };

	InRangeValidator<int> codesValidator{ 0, 1000 };
	MultiArg<int> codes{ codesValidator, 'c', "codes" };

	InRangeValidator<float> pricesValidator{ 0.f, 10000.f };
	MultiArg<float> prices{ pricesValidator, 'p', "prices" };

	FileFormatValidator<std::string> outputValidator{};
	MultiArg<std::string> output{ outputValidator, 'o', "output" };

	SingleArg<UserChrono> debugSleep{ 'd', "debug-sleep" };
	MultiArg<UserChrono> skipTimes{ 'S', "skip-times" };

	parser.Add(&help);
	parser.Add(&fast);
	parser.Add(&sleep);
	parser.Add(&megafast);
	parser.Add(&lock);
	parser.Add(&warnas);
	parser.Add(&warnings);
	parser.Add(&fraction);
	parser.Add(&name);

	parser.Add(&authorizes);
	parser.Add(&codes);
	parser.Add(&prices);
	parser.Add(&output);
	parser.Add(&debugSleep);
	parser.Add(&skipTimes);

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
		if (warnas.IsDefined()) {
			cout << "Int argument: " << warnas.GetOption() << "/" << warnas.GetLongOption() << " " << warnas.GetValue() << endl;
		}
		if (warnings.IsDefined()) {
			cout << "Int argument: " << warnings.GetOption() << "/" << warnings.GetLongOption() << " " << warnings.GetValue() << endl;
		}
		if (fraction.IsDefined()) {
			cout << "Float argument: " << fraction.GetOption() << "/" << fraction.GetLongOption() << " " << fraction.GetValue() << endl;
		}
		if (name.IsDefined()) {
			cout << "String argument: " << name.GetOption() << "/" << name.GetLongOption() << " " << name.GetValue() << endl;
		}
		if (authorizes.IsDefined()) {
			cout << "MultiBool argument: " << authorizes.GetOption() << "/" << authorizes.GetLongOption() << " ";
			for (auto value : authorizes.GetValues()) {
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
		if (prices.IsDefined()) {
			cout << "MultiFloat argument: " << prices.GetOption() << "/" << prices.GetLongOption() << " ";
			for (auto value : prices.GetValues()) {
				cout << value << ", ";
			}
			cout << endl;
		}
		if (output.IsDefined()) {
			cout << "MultiString argument: " << output.GetOption() << "/" << output.GetLongOption() << " ";
			for (auto value : output.GetValues()) {
				cout << value << ", ";
			}
			cout << endl;
		}
		if (debugSleep.IsDefined()) {
			cout << "UserType argument: " << debugSleep.GetOption() << "/" << debugSleep.GetLongOption() << " " << debugSleep.GetValue().GetMicroseconds().count() << endl;
		}
		if(skipTimes.IsDefined()) {
			cout << "MultiUserType argument: " << skipTimes.GetOption() << "/" << skipTimes.GetLongOption() << " ";
			for (auto value : skipTimes.GetValues()) {
				cout << value.GetMicroseconds().count() << ", ";
			}
			cout << endl;
		}
	}
	else
		cout << result.GetError().Message << endl;

	return 0;
}