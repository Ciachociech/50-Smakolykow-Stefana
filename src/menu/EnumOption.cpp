#include "../../include/menu/EnumOption.h"

EnumOption::EnumOption() : BasicOption(), valuesCount(0) {}

std::string EnumOption::getValueAsString() { return enumNames[getValue()]; }

bool EnumOption::addEnum(std::string name)
{
	if (findEnumName(name) == -1) { enumNames.push_back(name); return true; }
	return false;
}

bool EnumOption::setByName(std::string name)
{
	int foundIndex = findEnumName(name);
	if (foundIndex != -1) { setValue(foundIndex); return true; }
	return false;
}

int EnumOption::findEnumName(std::string name)
{
	for (int index = 0; index < enumNames.size(); index++)
	{
		if (enumNames[index] == name) { return index; }
	}
	return -1;
}
