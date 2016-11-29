#include "stdafx.h"

/*
0 -- ROOT
1 -- KEY
2 -- VALUE
3 -- BLOCK
*/

bool checkInput(string inputVal);
string cleaningFile(string file);

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
	string line;
	string file = "";

	for (int i = 0; i < N; i++) {
		getline(cin, line);
		file += line;
	}

	string pureFile = cleaningFile(file);

	// parser work
	Parser parser;
	vector<Element> arrayElements;

	parser.parseFile(pureFile, arrayElements);
	
	return 0;
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

string cleaningFile(string file)
{
	string pureFile = "";
	int inquotes = 0;

	for (int i = 0; i < (int)file.size(); i++) {
		if (file[i] == '\'') {
			inquotes += 1;
			inquotes %= 2;
		}
		if ( (isalnum(file[i]) || file[i] == '\'' || file[i] == '(' || file[i] == ')' 
			|| file[i] == ';' || file[i] == '=') || (inquotes) ) {
			pureFile.push_back(file[i]);

		}
	}
	return pureFile;
}