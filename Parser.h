#pragma once

#include "stdafx.h"

enum State { INITIALIZATION, DETECT_TYPE, WRITE_KEY, WRITE_VALUE, OPEN_BLOCK, CLOSE_BLOCK, ENABLE_PAIR, FORM_ELEMENT };

class Parser
{
private:
	char currentChar;
	char nextChar;
	State state;
	Element emptyElement;
	Element *fatherPointer;
	Type typeBuffer;
	string contentBuffer;
	bool itPair;
	bool inQuotes;
	// functions for each state 
	void doInitialization(Element *root);
	void doDetectType();
	void doWriteKey();
	void doWriteValue();
	void doOpenBlock();
	void doCloseBlock();
	void doEnablePair();
	void doFormElement();
public:
	Parser() : state(INITIALIZATION), typeBuffer(DEFAULT), contentBuffer(""), itPair(false), inQuotes(false) {}
	void parseFile(string file, Element &root);
};