#include "stdafx.h"

void Parser::parse(char inputChar, Element &root)
{
	if (formInput(inputChar) || inputChar == '\0')
	{
		bool work = true;
		while (work)
			work = parsing(inputChar, root);
	}
}

bool Parser::parsing(char currentChar, Element & root)
{
	switch (state) {
	case INITIALIZATION:
		return this->doInitialization(&root);
	case DETECT_TYPE:
		return this->doDetectType(currentChar);
	case WRITE_KEY:
		return this->doWriteKey(currentChar);
	case WRITE_VALUE:
		return this->doWriteValue(currentChar);
	case OPEN_BLOCK:
		return this->doOpenBlock(currentChar);
	case CLOSE_BLOCK:
		return this->doCloseBlock(currentChar);
	case ENABLE_PAIR:
		return this->doEnablePair(currentChar);
	case FORM_ELEMENT:
		return this->doFormElement(currentChar);
	}
}

bool Parser::doInitialization(Element * root)
{
	// add root 
	root->setRootElement();
	this->fatherPointer = root;
	// switch state
	this->state = DETECT_TYPE;
	return true;
}

bool Parser::doDetectType(char currentChar)
{
	// detect type & switch state
	if (currentChar == '\'') {
		if (this->itPair) {
			this->state = WRITE_VALUE;
			this->typeBuffer = VALUE;
		}
		else {
			this->state = WRITE_KEY;
			this->typeBuffer = KEY;
		}
	}
	if (isalnum(currentChar)) {
		this->state = WRITE_VALUE;
		this->typeBuffer = VALUE;
	}
	if (currentChar == '(') {
		this->state = OPEN_BLOCK;
		this->typeBuffer = BLOCK;
	}
	if (currentChar == '=') {
		this->itPair = true;
		this->state = ENABLE_PAIR;
	}
	if (currentChar == ')')
		this->state = CLOSE_BLOCK;
	// clear content
	this->contentBuffer = "";
	// if semicolon
	if (currentChar == ';') {
		// add content
		this->contentBuffer.push_back(currentChar);
		this->fatherPointer->getLastChild()->addContent(this->contentBuffer);
		return false;
	}
	if (currentChar == '\0')
		return false;
	return true;
}

bool Parser::doWriteKey(char currentChar)
{
	this->contentBuffer.push_back(currentChar);
	// if sign active
	if (this->sign && !this->inQuotes) {
		if (this->itPair)
			this->typeBuffer = VALUE;
		this->state = FORM_ELEMENT;
		return true;
	}
	return false;
}

bool Parser::doWriteValue(char currentChar)
{
	if (!(currentChar == '(' || currentChar == ')' || currentChar == '\0') || this->inQuotes)
		this->contentBuffer.push_back(currentChar);
	// if sign active
	if (this->sign && !this->inQuotes) {
		this->state = FORM_ELEMENT;
		return true;
	}
	return false;
}

bool Parser::doOpenBlock(char currentChar)
{
	// if pair enable
	if (this->itPair == true)
		this->itPair = false;
	// form block
	this->contentBuffer.push_back(currentChar);
	this->emptyElement.setType(this->typeBuffer);
	this->emptyElement.setContent(this->contentBuffer);
	// form struct
	this->fatherPointer->addChildElement(new Element(emptyElement));
	// change father
	this->fatherPointer = fatherPointer->getLastChild();
	// switch state
	this->state = DETECT_TYPE;
	return false;
}

bool Parser::doCloseBlock(char currentChar)
{
	// add content
	this->contentBuffer.push_back(currentChar);
	fatherPointer->addContent(this->contentBuffer);
	// change father
	this->fatherPointer = fatherPointer->getFather();
	// switch state
	this->state = DETECT_TYPE;
	return false;
}

bool Parser::doEnablePair(char currentChar)
{
	// add content
	this->contentBuffer.push_back(currentChar);
	this->fatherPointer->getLastChild()->addContent(this->contentBuffer);
	// switch state
	this->state = DETECT_TYPE;
	return false;
}

bool Parser::doFormElement(char currentChar)
{
	// form element
	this->emptyElement.setType(this->typeBuffer);
	this->emptyElement.setContent(this->contentBuffer);
	// form struct
	this->fatherPointer->addChildElement(new Element(emptyElement));
	// switch state
	this->state = DETECT_TYPE;
	// disable itPair
	this->itPair = false;
	if ((currentChar == '(' || currentChar == ')') && (this->contentBuffer.size() != 0))
		return true;
	return false;
}

bool Parser::formInput(char inputChar)
{
	// check inQuotes
	if (inputChar == '\'') {
		if (this->inQuotes)
			this->inQuotes = false;
		else
			this->inQuotes = true;
	}
	// check sign
	if ((this->inQuotes == false && (inputChar == '\'' || inputChar == '(' || inputChar == '\0'
		|| inputChar == ')' || inputChar == '=' || inputChar == ';' || inputChar == '\''))
		|| (this->inQuotes == true && inputChar == '\'')) {
		this->sign = true;
	}
	else {
		this->sign = false;
	}
	// return result
	if (this->inQuotes == false && !(isalnum(inputChar) || inputChar == '\'' || inputChar == '('
		|| inputChar == ')' || inputChar == '=' || inputChar == ';' || inputChar == '\'')) {
		return false;
	}
	return true;
}