#include "..\..\include\menu\RangeOption.h"

RangeOption::RangeOption(int minValue, int maxValue, int defaultValue) : BasicOption(defaultValue), minValue(minValue), maxValue(maxValue) {}

RangeOption::RangeOption(int minValue, int maxValue) : BasicOption(), minValue(minValue), maxValue(maxValue) {}

RangeOption::RangeOption() : BasicOption(), minValue(0), maxValue(0) {}

std::string RangeOption::getValueAsString()
{
	int percent = 100 * getValue() / maxValue;
	return std::to_string(percent) + "%";
}

int RangeOption::getMinValue() { return minValue; }

int RangeOption::getMaxValue() { return maxValue; }

void RangeOption::setMinValue(int value) { this->minValue = value; }

void RangeOption::setMaxValue(int value) { this->maxValue = value; }