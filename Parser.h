#pragma once

#include "stdafx.h"

enum State { INITIALIZATION, DETECT_TYPE, WRITE_KEY, WRITE_VALUE, OPEN_BLOCK, CLOSE_BLOCK, FORM_PAIR, FORM_ELEMENT };

class Parser
{
private:
	char currentChar;
	char nextChar;
	State state;
	Element * root;
	Element emptyElement;
	Element *fatherPointer;
	Type typeBuffer;
	string contentBuffer;
	bool formPair;

	//each state functions
	void doInitialization(Element * root);
	void doDetectType();
	void doWriteKey();
	void doWriteValue();
	void doOpenBlock();
	void doCloseBlock();
	void doFormPair();
	void doFormElement();
public:
	Parser() : state(INITIALIZATION), typeBuffer(DEFAULT), contentBuffer(""), formPair(false) {}
	Element *parseFile(string file);
};