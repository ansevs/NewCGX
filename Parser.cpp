#include "stdafx.h"

bool Parser::formElement(char inputChar)
{
	if (formInput(inputChar) || inputChar == '\0')
	{
		bool work = true;
		while (work) {
			work = parsing(inputChar);
			if (this->formed)
				return true;
		}
	}
	return false;
}

Element Parser::getFormedElement()
{
	return this->container;
}

bool Parser::parsing(char currentChar)
{
	switch (state) {
	case INITIALIZATION:
		return this->doInitialization();
	case DETECT_TYPE:
		return this->doDetectType(currentChar);
	case WRITE_KEY:
		return this->doWriteKey(currentChar);
	case WRITE_VALUE:
		return this->doWriteValue(currentChar);
	case WRITE_SIGN:
		return this->doWriteSign(currentChar);
	case FORM_ELEMENT:
		return this->doFormElement(currentChar);
	}
}

bool Parser::doInitialization()
{
	// clear
	this->formed = false;
	this->contentBuffer = "";
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
	if (currentChar == '(' || currentChar == ')' ||
		currentChar == ';' || currentChar == '=')
		this->state = WRITE_SIGN;
	// end
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
	if (!(currentChar == '\0') || this->inQuotes)
		this->contentBuffer.push_back(currentChar);
	// special case
	if (currentChar == '(')
		this->currentLevel++;
	if (currentChar == ')') {
		if (this->currentLevel != 0)
			this->currentLevel--;
	}
	// if sign active
	if (this->sign && !this->inQuotes) {
		this->state = FORM_ELEMENT;
		return true;
	}
	return false;
}

bool Parser::doWriteSign(char currentChar)
{
	// write sign
	this->contentBuffer.push_back(currentChar);
	// set rules
	switch (currentChar)
	{
	case '(':
		this->typeBuffer = BLOCK;
		this->currentLevel++;
		break;
	case ')':
		this->typeBuffer = BLOCK;
		if (this->currentLevel != 0)
			this->currentLevel--;
		break;
	case ';':
		this->typeBuffer = SEMICOLON;
		break;
	case '=':
		this->typeBuffer = EQUALLY;
		this->itPair = true;
		break;
	}
	// switch state
	this->state = FORM_ELEMENT;
	return true;
}

bool Parser::doFormElement(char currentChar)
{
	// form element
	this->container.setType(this->typeBuffer);
	this->container.setContent(this->contentBuffer);
	this->container.setLevel(this->currentLevel);
	// correction level
	if (this->contentBuffer == "(")
		this->container.setLevel(this->currentLevel - 1);
	// special case
	if (currentChar == '(' && this->typeBuffer == VALUE)
		this->container.setLevel(this->currentLevel - 1);
	if (currentChar == ')' && this->typeBuffer == VALUE)
		this->container.setLevel(this->currentLevel + 1);
	// disable itPair
	if (this->typeBuffer != EQUALLY)
		this->itPair = false;
	// switch state
	this->formed = true;
	this->state = INITIALIZATION;
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