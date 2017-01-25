#pragma once

#include "stdafx.h"

class Formatter
{
private:
	Type prevElementType;
	void indent(int tabCount);
	void print(Element &container);
public:
	Formatter() : prevElementType(DEFAULT) {}
	void formatAndPrint(Element &container);
};