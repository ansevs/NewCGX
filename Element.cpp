#include "stdafx.h"
#include "Element.h"

void Element::showElement(Element *element)
{
	cout << "Info: " << endl;
	cout << "TYPE: " << (int)element->type << endl;
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

void Element::addChildElement(Element *child)
{
	child->rootElement = this;
	this->childElements.push_back(child);
}

void Element::showCurentElement()
{
	showElement(this);
}

void Element::showFather()
{
	if ( (this->rootElement == NULL) || (this->type == ROOT) )
		cout << "It is a ROOT element!" << endl;		
	else
		showElement(this->rootElement);
}

void Element::showChildren()
{
	if (this->childElements.size() != 0) {
		vector<Element *>::iterator it;
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
	this->childElements.shrink_to_fit();
	this->type = DEFAULT;
	this->content = "";
}

void Element::erase()
{
	// find this element like child and erase
	int counter = 0;
	vector<Element *>::iterator itChild;
	for (itChild = rootElement->childElements.begin(); itChild != rootElement->childElements.end(); itChild++) {
		if ((*itChild) == this)
			break;
		counter++;
	}
	rootElement->childElements.erase(rootElement->childElements.begin() + counter);

	// pointers redistribution
	vector<Element *>::iterator it;
	for (it = this->childElements.begin(); it != this->childElements.end(); it++) {
		(*it)->rootElement = this->rootElement;
		rootElement->childElements.insert(rootElement->childElements.begin() + counter, *it);
		counter++;
	}
}