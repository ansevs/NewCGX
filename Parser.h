#pragma once

#include "stdafx.h"

enum State { INITIALIZATION, DETECT_TYPE, WRITE_KEY, WRITE_VALUE, OPEN_BLOCK, CLOSE_BLOCK, ENABLE_PAIR, FORM_ELEMENT };

class Parser
{
private:
	State state;
	Element emptyElement;
	Element *fatherPointer;
	Type typeBuffer;
	string contentBuffer;
	bool itPair;
	bool inQuotes;
	bool sign;
	// functions for each state 
	bool doInitialization(Element * root);
	bool doDetectType(char currentChar);
	bool doWriteKey(char currentChar);
	bool doWriteValue(char currentChar);
	bool doOpenBlock(char currentChar);
	bool doCloseBlock(char currentChar);
	bool doEnablePair(char currentChar);
	bool doFormElement(char currentChar);
	// other functions
	bool parsing(char currentChar, Element & root);
	bool formInput(char inputChar);
public:
	Parser() : state(INITIALIZATION), typeBuffer(DEFAULT), contentBuffer(""), itPair(false), inQuotes(false), sign(false) {}
	void parse(char inputChar, Element &root);
};