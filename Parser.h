#pragma once

#include "stdafx.h"

enum State { INITIALIZATION, DETECT_TYPE, WRITE_KEY, WRITE_VALUE, OPEN_BLOCK, CLOSE_BLOCK, FORM_PAIR, FORM_ELEMENT };

class Parser
{
private:
	char currentChar;
	char nextChar;
	State state;
	Element emptyElement;
	shared_ptr<Element> fatherPointer;
	Type typeBuffer;
	string contentBuffer;
	bool formPair;

	//each state functions
	void doInitialization(shared_ptr<Element> root);
	void doDetectType();
	void doWriteKey();
	void doWriteValue();
	void doOpenBlock();
	void doCloseBlock();
	void doFormPair();
	void doFormElement();
public:
	Parser() : state(INITIALIZATION), typeBuffer(DEFAULT), contentBuffer(""), formPair(false) {}
	shared_ptr<Element> parseFile(string file);
};