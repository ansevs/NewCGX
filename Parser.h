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
	Type typeBuffer;
	string contentBuffer;
	bool formPair;
	int currentPointer;
	int fatherPointer;

	//each state functions
	void doInitialization(vector<Element> & arrayElements);
	void doDetectType();
	void doWriteKey();
	void doWriteValue();
	void doOpenBlock();
	void doCloseBlock();
	void doFormPair();
	void doFormElement(vector<Element> & arrayElements);
public:
	Parser() : state(INITIALIZATION), typeBuffer(DEFAULT), contentBuffer(""), formPair(false), currentPointer(0), fatherPointer(0) {}
	void parseFile(string file, vector<Element> & arrayElements);
};