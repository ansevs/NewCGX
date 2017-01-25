#include "stdafx.h"

void Formatter::indent(int tabCount)
{
	for (int i = 0; i < tabCount; i++) {
		cout << "    ";
	}
}

void Formatter::print(Element &container)
{
	if (this->prevElementType != DEFAULT)
		cout << endl;
	this->indent(container.getLevel());
	cout << container.getContent();
}

void Formatter::formatAndPrint(Element &container)
{
	// block rules
	if (container.getType() == BLOCK) {
		print(container);
	}
	// sign rules
	if (container.getType() == SEMICOLON || container.getType() == EQUALLY) {
		cout << container.getContent();
	}
	// key rules
	if (container.getType() == KEY) {
		print(container);
	}
	// value rules
	if (container.getType() == VALUE) {
		// special case
		char specialChar = container.getContent().back();
		if (specialChar == '(' || specialChar == ')')
			container.popBackContent();
		// common case
		if (this->prevElementType == EQUALLY) {
			cout << container.getContent();
		} else {
			print(container);
		}
		// special case end
		if (specialChar == '(') {
			cout << endl;
			this->indent(container.getLevel());
			cout << '(';
		}
		if (specialChar == ')') {
			cout << endl;
			this->indent(container.getLevel()-1);
			cout << ')';
		}
	}
	// save prevType
	this->prevElementType = container.getType();
}