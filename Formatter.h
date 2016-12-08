#pragma once

#include "stdafx.h"

class Formatter
{
private:
	int tabCounter;
	Element *fatherPointer;

	void indent(int tabCount);
	void formatting(Element *father);
public:
	Formatter() : tabCounter(0) {}
	void printFormattedFile(Element &root);
};