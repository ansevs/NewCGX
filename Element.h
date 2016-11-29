#pragma once

#include "stdafx.h"

#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

enum Type { DEFAULT, ROOT, KEY, VALUE, BLOCK, PAIR };

class Element
{
private:
	Element *rootElement;
	vector<Element *> childElements;
	Type type;
	string content;
	void showElement(Element *element);
public:
	Element() : type(DEFAULT), content("") {}
	Element(Type elementType, string elementContent) : type(elementType), content(elementContent) {}
	Element(const Element & element);
	void setRootElement();
	void setType(Type newType);
	void setContent(string newContent);
	void addChildElement(Element *child);
	void showCurentElement();
	void showFather();
	void showChildren();
	void clear();
	void erase();
};