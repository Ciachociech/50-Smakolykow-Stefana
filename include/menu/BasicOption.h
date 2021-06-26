#pragma once

#include "..\..\include\external_dependencies.h"

class BasicOption
{
public:
	BasicOption();
	BasicOption(int value);
	virtual ~BasicOption();

	virtual std::string getValueAsString() = 0;
	int getValue();
	void setValue(int value);
private:
	int stdValue;
};

