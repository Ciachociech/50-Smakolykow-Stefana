#pragma once

#include <vector>
#include <memory>

#include "..\menu\RangeOption.h"

class OptionsManager
{
public:
	OptionsManager();
	virtual ~OptionsManager();

	bool decreaseOptionValue(int index);
	bool increaseOptionValue(int index);
	void exterminate();

	void addOption(int minValue, int maxValue, int defaultValue);
	void addOption(int minValue, int maxValue);
	std::string getOptionValueString(int index);
	int getOptionValue(int index);
private:
	std::vector<std::unique_ptr<BasicOption>> options;
};

