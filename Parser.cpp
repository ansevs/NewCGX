#include "stdafx.h"

shared_ptr<Element> Parser::parseFile(string file)
{
	shared_ptr<Element> root(new Element(emptyElement));
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
			this->doInitialization(root);
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
			this->doFormElement();
			break;
		}
	}
	return root;
}

void Parser::doInitialization(shared_ptr<Element> root)
{
	// add root 
	root->setRootElement();
	fatherPointer = root;	
	// switch state
	this->state = DETECT_TYPE;
}

void Parser::doDetectType()
{
	// detect type & switch state
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
	// clear content
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

void Parser::doFormElement()
{
	// form element
	emptyElement.setType(this->typeBuffer);
	emptyElement.setContent(this->contentBuffer);
	// form struct
	fatherPointer->addChildElement(new Element(emptyElement));
	// switch state
	this->state = DETECT_TYPE;
}