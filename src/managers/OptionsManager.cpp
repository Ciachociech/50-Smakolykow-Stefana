#include "..\..\include\managers\OptionsManager.h"

OptionsManager::OptionsManager() : options() {}

OptionsManager::~OptionsManager() { exterminate(); }

bool OptionsManager::decreaseOptionValue(int index)
{
	if (index >= 0 && index < options.size())
	{
		if (typeid(dynamic_cast<RangeOption*>(options[index].get())) == typeid(dynamic_cast<RangeOption*>(std::make_unique<RangeOption>().get())))
		{
			if (options[index]->getValue() > dynamic_cast<RangeOption*>(options[index].get())->getMinValue())
			{
				options[index]->setValue(options[index]->getValue() - 1);
				return true;
			}
		}
	}
	return false;
}

bool OptionsManager::increaseOptionValue(int index)
{
	if (index >= 0 && index < options.size())
	{
		if (typeid(dynamic_cast<RangeOption*>(options[index].get())) == typeid(dynamic_cast<RangeOption*>(std::make_unique<RangeOption>().get())))
		{
			if (options[index]->getValue() < dynamic_cast<RangeOption*>(options[index].get())->getMaxValue())
			{
				options[index]->setValue(options[index]->getValue() + 1);
				return true;
			}
		}
	}
	return false;
}

void OptionsManager::exterminate() { options.clear(); }

void OptionsManager::addOption(int minValue, int maxValue, int defaultValue)
{
	options.push_back(std::make_unique<RangeOption>(minValue, maxValue, defaultValue));
}

void OptionsManager::addOption(int minValue, int maxValue) { options.push_back(std::make_unique<RangeOption>(minValue, maxValue)); }

std::string OptionsManager::getOptionValueString(int index)
{
	if (index >= 0 && index < options.size())
	{
		return options[index]->getValueAsString();
	}
	return std::string();
}

int OptionsManager::getOptionValue(int index)
{
	if (index >= 0 && index < options.size())
	{
		return options[index]->getValue();
	}
	return -1;
}