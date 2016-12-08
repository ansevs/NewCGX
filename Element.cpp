#include "stdafx.h"
#include "Element.h"

void Element::showElement(Element *element)
{
	cout << "Info: " << endl;
	cout << "TYPE: ";
	switch (element->type)
	{
	case DEFAULT:
		cout << "DEFAULT" << endl;
		break;
	case ROOT:
		cout << "ROOT" << endl;
		break;
	case KEY:
		cout << "KEY" << endl;
		break;
	case VALUE:
		cout << "VALUE" << endl;
		break;
	case BLOCK:
		cout << "BLOCK" << endl;
		break;
	}
	cout << "CONTENT: " << element->content << endl;
	cout << "--------------------" << endl;
}

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

void Element::showCurentElement()
{
	showElement(this);
}

void Element::showFather()
{
	if ((this->rootElement == NULL) /*|| (this->type == ROOT)*/)
		cout << "It is a ROOT element!" << endl;
	else
		showElement(this->rootElement);
}

void Element::showChildren()
{
	if (this->childElements.size() != 0) {
		list<Element *>::iterator it;
		for (it = this->childElements.begin(); it != this->childElements.end(); it++)
			showElement(*it);
	}
	else {
		cout << "This element has not children!" << endl;
	}
}

void Element::clear()
{
	this->rootElement = NULL;
	this->childElements.clear();
	this->type = DEFAULT;
	this->content = "";
}

void Element::erase()
{
	// find this element like child and erase
	int counter = 0;
	list<Element *>::iterator itChild;
	for (itChild = rootElement->childElements.begin(); itChild != rootElement->childElements.end(); itChild++) {
		if ((*itChild) == this)
			break;
		counter++;
	}
	list<Element *>::iterator iter1;
	iter1 = rootElement->childElements.begin();
	advance(iter1, counter);
	rootElement->childElements.erase(iter1);

	// pointers redistribution
	list<Element *>::iterator it;
	for (it = this->childElements.begin(); it != this->childElements.end(); it++) {
		(*it)->rootElement = this->rootElement;

		list<Element *>::iterator iter;
		iter = rootElement->childElements.begin();
		advance(iter, counter);
		rootElement->childElements.insert(iter, *it);		
		counter++;
	}
}