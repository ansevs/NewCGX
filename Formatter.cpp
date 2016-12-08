#include "stdafx.h"

void Formatter::indent(int tabCount)
{
	for (int i = 0; i < tabCount; i++) {
		cout << "    ";
	}
}

void Formatter::formatting(Element *root)
{
	// auxiliary variable
	string currentContent = "";
	Type currentType = DEFAULT;
	Type nextElementType = DEFAULT;
	Type prevElementType = DEFAULT;
	// formatting & print
	for (int i = 0; i < root->getChildrenQuantity(); i++) {
		currentContent = root->getChild(i)->getContent();
		currentType = root->getChild(i)->getType();
		if (i == root->getChildrenQuantity() - 1)
			nextElementType = DEFAULT;
		else
			nextElementType = root->getChild(i + 1)->getType();
		if (i == 0)
			prevElementType = DEFAULT;
		else
			prevElementType = root->getChild(i - 1)->getType();
		// print content (if element is not block)
		if (currentType != BLOCK) {
			// if pair
			if (currentType == KEY && nextElementType == VALUE) {
				this->indent(this->tabCounter);
				cout << currentContent;
			}
			// if not pair
			else {
				if (!(prevElementType == KEY && currentType == VALUE))
					this->indent(this->tabCounter);
				cout << currentContent << endl;
			}
		}
		// if element is block
		else {
			// if block is empty
			if (root->getChild(i)->getChildrenQuantity() == 0) {
				this->indent(this->tabCounter);
				cout << currentContent.front() << endl;
				if (currentContent.back() == ')') {
					this->indent(this->tabCounter);
					cout << currentContent.back() << endl;
				}
				else {
					currentContent.erase(0,1);
					this->indent(this->tabCounter);
					cout << currentContent << endl;
				}
			}
			// if block is not empty
			else {
				// open block
				this->indent(this->tabCounter);
				cout << currentContent.front() << endl;
				this->tabCounter++;
				// recursion
				this->formatting(root->getChild(i));
				// close block
				this->tabCounter--;
				if (currentContent.back() == ')') {
					this->indent(this->tabCounter);
					cout << currentContent.back() << endl;
				}
				else {
					currentContent.erase(0,1);
					this->indent(this->tabCounter);
					cout << currentContent << endl;
				}
			}
		}
	}
}

void Formatter::printFormattedFile(Element &root)
{
	// set father
	this->fatherPointer = &root;
	// formatting
	this->formatting(fatherPointer);
}