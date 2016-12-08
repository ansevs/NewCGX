#include "stdafx.h"

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
	
	// cleaning file
	string pureFile = cleaningFile(file);
	
	// create empty root element
	Element root;
	
	// parser work
	Parser parser;
	parser.parseFile(pureFile, root);

	// formatter work
	Formatter form;
	form.printFormattedFile(root);

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
	bool inquotes = false;

	for (int i = 0; i < (int)file.size(); i++) {
		if (file[i] == '\'') {
			if (inquotes)
				inquotes = false;
			else
				inquotes = true;
		}
		if (isalnum(file[i]) || file[i] == '\'' || file[i] == '(' || file[i] == ')'
			|| file[i] == ';' || file[i] == '=' || (inquotes)) {
			pureFile.push_back(file[i]);
		}
	}
	return pureFile;
}