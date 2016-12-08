#include "stdafx.h"
#include "Element.h"

Element::Element(const Element & element)
{
	this->type = element.type;
	this->content = element.content;
}

void Element::setRootElement()
{
	this->rootElement = NULL;
	this->type = ROOT;
	this->content = "ROOT element";
}

void Element::setType(Type newType)
{
	this->type = newType;
}

void Element::setContent(string newContent)
{
	this->content = newContent;
}

void Element::addContent(string addedContent)
{
	this->content += addedContent;
}

void Element::addChildElement(Element *child)
{
	child->rootElement = this;
	this->childElements.push_back(child);
}

Type Element::getType()
{
	return this->type;
}

string Element::getContent()
{
	return this->content;
}

Element *Element::getFather()
{
	return this->rootElement;
}

int Element::getChildrenQuantity()
{
	return this->childElements.size();
}

Element *Element::getChild(int num)
{
	list<Element *>::iterator iter;
	iter = this->childElements.begin();
	if (num < this->childElements.size()) {
		advance(iter, num);
		return *iter;
	} else {
		cout << "NUM > SIZE. First child is returned." << endl;
		return this->childElements.front();
	}
}

Element *Element::getLastChild()
{
	return this->childElements.back();
}