#pragma once

#include "stdafx.h"

class Formatter
{
private:
	int tabCounter;
	void indent(int tabCount);
	void formatting(Element *root);
public:
	Formatter() : tabCounter(0) {}
	void printFormattedText(Element &root);
};