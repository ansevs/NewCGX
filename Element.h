#pragma once

#include "stdafx.h"

#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

enum Type { DEFAULT, ROOT, KEY, VALUE, BLOCK };

class Element
{
private:
	Element *rootElement;
	list<Element *> childElements;	
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
	void addContent(string addedContent);
	void addChildElement(Element *child);
	Type getType();
	string getContent();
	Element *getFather();
	int getChildrenQuantity();
	Element *getChild(int num);
	Element *getLastChild();
	void showCurentElement();
	void showFather();
	void showChildren();
	void clear();
	void erase();
};