#pragma once

#include "stdafx.h"

#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

enum Type { DEFAULT, KEY, VALUE, BLOCK, SEMICOLON, EQUALLY };

class Element
{
private:
	Type type;
	string content;
	int level;
public:
	Element() : type(DEFAULT), content(""), level(0) {}
	Element(const Element & element);
	void setType(Type newType);
	void setContent(string newContent);
	void popBackContent();
	void setLevel(int newLevel);
	Type getType();
	string getContent();
	int getLevel();
};