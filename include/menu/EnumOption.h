#pragma once

#include "BasicOption.h"

class EnumOption : public BasicOption
{
public:
	EnumOption();

	std::string getValueAsString() override;
	bool addEnum(std::string name);
	bool setByName(std::string name);

private:
	int valuesCount;
	std::vector<std::string> enumNames;

	int findEnumName(std::string name);
};

