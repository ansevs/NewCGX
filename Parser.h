#pragma once

#include "stdafx.h"

enum State { INITIALIZATION, DETECT_TYPE, WRITE_KEY, WRITE_VALUE, WRITE_SIGN, FORM_ELEMENT };

class Parser
{
private:
	State state;
	Type typeBuffer;
	string contentBuffer;
	int currentLevel;
	Element container;
	bool itPair;
	bool inQuotes;
	bool sign;
	bool formed;
	// functions for each state
	bool doInitialization();
	bool doDetectType(char currentChar);
	bool doWriteKey(char currentChar);
	bool doWriteValue(char currentChar);
	bool doWriteSign(char currentChar);
	bool doFormElement(char currentChar);
	// other functions
	bool parsing(char currentChar);
	bool formInput(char inputChar);
public:
	Parser() : state(DETECT_TYPE), typeBuffer(DEFAULT), contentBuffer(""), currentLevel(0),
		formed(false), itPair(false), inQuotes(false), sign(false) {}
	bool formElement(char inputChar);		// return "true" if element is formed, else return "false"
	Element getFormedElement();
};