#include "stdafx.h"

void Parser::parseFile(string file, Element &root)
{
	int counter = 0;
	while ( (counter != (int)file.size()) || (this->state != DETECT_TYPE) ) {
		// set chars
		this->currentChar = file[counter];
		if (counter >= ( (int)file.size() - 1) )
			this->nextChar = '\0';
		else
			this->nextChar = file[counter + 1];
		// work
		switch (state) {
		case INITIALIZATION:
			this->doInitialization(&root);
			break;
		case DETECT_TYPE:
			this->doDetectType();
			break;
		case WRITE_KEY:
			this->doWriteKey();
			counter++;
			break;
		case WRITE_VALUE:
			this->doWriteValue();
			counter++;
			break;
		case OPEN_BLOCK:
			this->doOpenBlock();
			counter++;
			break;
		case CLOSE_BLOCK:
			this->doCloseBlock();
			counter++;
			break;
		case ENABLE_PAIR:
			this->doEnablePair();
			counter++;
			break;
		case FORM_ELEMENT:
			this->doFormElement();
			break;
		}
	}
}

void Parser::doInitialization(Element *root)
{
	// add root 
	root->setRootElement();
	this->fatherPointer = root;
	// switch state
	this->state = DETECT_TYPE;
}

void Parser::doDetectType()
{
	// detect type & switch state
	if (this->currentChar == '\'') {
		if (this->itPair) {
			this->state = WRITE_VALUE;
			this->typeBuffer = VALUE;
		}
		else {
			this->state = WRITE_KEY;
			this->typeBuffer = KEY;
		}
	}
	if (isalnum(this->currentChar)) {
		this->state = WRITE_VALUE;
		this->typeBuffer = VALUE;
	}
	if (this->currentChar == '(') {
		this->state = OPEN_BLOCK;
		this->typeBuffer = BLOCK;
	}
	if (this->currentChar == '=') {
		this->itPair = true;
		this->state = ENABLE_PAIR;
	}
	if (this->currentChar == ')')
		this->state = CLOSE_BLOCK;
	// clear content
	this->contentBuffer = "";
}

void Parser::doWriteKey()
{
	this->contentBuffer.push_back(currentChar);
	// enable inQuotes
	if (this->contentBuffer.front() == '\'' && this->contentBuffer.size() == 1)
		this->inQuotes = true;
	// disable inQuotes
	if (this->contentBuffer.back() == '\'' && this->contentBuffer.size() != 1) {
		this->inQuotes = false;
		this->state = FORM_ELEMENT;
	}
	// if first str is value
	if (this->currentChar == '\'' && this->nextChar == ';')
		this->state = WRITE_KEY;
	// if end val
	if ((this->currentChar == ';') && (this->inQuotes == false)) {
		this->typeBuffer = VALUE;
		this->state = FORM_ELEMENT;
	}	
}

void Parser::doWriteValue()
{
	this->contentBuffer.push_back(currentChar);
	// enable inQuotes
	if (this->contentBuffer.front() == '\'' && this->contentBuffer.size() == 1)
		this->inQuotes = true;
	// switch state
	if ( ((this->currentChar == '\'') && (this->contentBuffer.size() != 1) && (this->nextChar != ';')) 
		|| ((this->currentChar == ';') && (this->inQuotes == false)) 
		|| ((this->nextChar == ')') && (this->inQuotes == false)) || (this->nextChar == '\0')) {
		this->state = FORM_ELEMENT;
	}
	// disable inQuotes
	if (this->contentBuffer.back() == '\'' && this->contentBuffer.size() != 1)
		this->inQuotes = false;
	// disable pair
	this->itPair = false;
}

void Parser::doOpenBlock()
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
}

void Parser::doCloseBlock()
{
	// add content
	this->contentBuffer.push_back(currentChar);
	if (currentChar == ')' && nextChar == ';') {
		this->state = CLOSE_BLOCK;
		return;
	} else {
		fatherPointer->addContent(this->contentBuffer);
	}
	// change father
	this->fatherPointer = fatherPointer->getFather();
	// switch state
	this->state = DETECT_TYPE;
}

void Parser::doEnablePair()
{
	// add content
	this->contentBuffer.push_back(currentChar);
	this->fatherPointer->getLastChild()->addContent(this->contentBuffer);
	// switch state
	this->state = DETECT_TYPE;
}

void Parser::doFormElement()
{
	// form element
	this->emptyElement.setType(this->typeBuffer);
	this->emptyElement.setContent(this->contentBuffer);
	// form struct
	this->fatherPointer->addChildElement(new Element(emptyElement));
	// switch state
	this->state = DETECT_TYPE;
}