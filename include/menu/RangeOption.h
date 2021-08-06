#pragma once

#include "BasicOption.h"

class RangeOption : public BasicOption
{
public:
	RangeOption(int minValue, int maxValue, int defaultValue);
	RangeOption(int minValue, int maxValue);
	RangeOption();

	std::string getValueAsString() override;
	int getMinValue();
	int getMaxValue();

	void setMinValue(int value);
	void setMaxValue(int value);
private:
	int minValue, maxValue;
};

