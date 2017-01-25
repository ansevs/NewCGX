#include "stdafx.h"

bool checkInput(string inputVal);

int main()
{
	// input value processing
	int N;
	string input;

	getline(cin, input);
	if (!(checkInput(input))) {
		cout << "Incorrect input format." << endl;
		return 0;
	}

	N = stoi(input);

	// init
	Parser parser;
	Formatter formatter;

	// start parsing
	for (int i = 0; i < N; i++) {
		char currentChar = NULL;
		while (cin.read(&currentChar, 1)) {
			if (currentChar == '\n')
				break;
			if (parser.formElement(currentChar)) {
				Element container = parser.getFormedElement();
				formatter.formatAndPrint(container);
			}
		}
	}
	// end parsing
	if (parser.formElement('\0')) {
		Element container = parser.getFormedElement();
		formatter.formatAndPrint(container);
	}

	return 1;
}

bool checkInput(string inputVal)
{
	bool correct = true;

	for (int i = 0; i < (int)inputVal.length(); i++) {
		if (!(inputVal[i] >= '0' && inputVal[i] <= '9'))
			correct = false;
	}

	if (correct)
		return true;
	return false;
}