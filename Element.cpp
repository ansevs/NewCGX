#include "stdafx.h"
#include "Element.h"

Element::Element(const Element & element)
{
	this->type = element.type;
	this->content = element.content;
	this->level = element.level;
}

void Element::setType(Type newType)
{
	this->type = newType;
}

void Element::setContent(string newContent)
{
	this->content = newContent;
}

void Element::popBackContent()
{
	this->content.pop_back();
}

void Element::setLevel(int newLevel)
{
	this->level = newLevel;
}

Type Element::getType()
{
	return this->type;
}

string Element::getContent()
{
	return this->content;
}

int Element::getLevel()
{
	return this->level;
}