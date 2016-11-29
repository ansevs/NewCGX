#include "stdafx.h"

void Parser::parseFile(string file, vector<Element> & arrayElements)
{
	// cleaning array
	arrayElements.clear();
	arrayElements.shrink_to_fit();

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
			this->doInitialization(arrayElements);
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
		case FORM_PAIR:
			this->doFormPair();
			break;
		case FORM_ELEMENT:
			this->doFormElement(arrayElements);
			break;
		}
	}
}

void Parser::doInitialization(vector<Element> & arrayElements)
{
	//add root 
	arrayElements.push_back(emptyElement);
	(*(arrayElements.begin())).setType(this->typeBuffer);
	(*(arrayElements.begin())).setContent(this->contentBuffer);
	(*(arrayElements.begin())).setRootElement();
	//switch state
	this->state = DETECT_TYPE;
}

void Parser::doDetectType()
{
	//detect type & switch state
	if (this->currentChar == '\'') {
		if (this->formPair) {
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
		this->formPair = true;
		this->state = FORM_PAIR;
		this->typeBuffer = PAIR;
	}
	if (this->currentChar == ')')
		this->state = CLOSE_BLOCK;
	//clear content
	this->contentBuffer = "";
}

void Parser::doWriteKey()
{
	this->contentBuffer.push_back(currentChar);
	if ((this->currentChar == '\'') && (this->contentBuffer.size() != 1)) {
		this->state = FORM_ELEMENT;
	}
}

void Parser::doWriteValue()
{}

void Parser::doOpenBlock()
{}

void Parser::doCloseBlock()
{}

void Parser::doFormPair()
{}

void Parser::doFormElement(vector<Element> & arrayElements)
{
	//form element
	arrayElements.push_back(emptyElement);
	currentPointer++;
	(*(arrayElements.begin() + currentPointer)).setType(this->typeBuffer);
	(*(arrayElements.begin() + currentPointer)).setContent(this->contentBuffer);
	(*(arrayElements.begin() + fatherPointer)).addChildElement(&(*(arrayElements.begin() + currentPointer)));
	//switch state
	this->state = DETECT_TYPE;
}