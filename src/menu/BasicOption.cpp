#include "..\..\include\menu\BasicOption.h"

BasicOption::BasicOption() : stdValue(0) {}

BasicOption::BasicOption(int value) : stdValue(value) {}

BasicOption::~BasicOption() {}

int BasicOption::getValue() { return stdValue; }

void BasicOption::setValue(int value) { this->stdValue = value; }
