#pragma once

#include "AdventRunner.h"

class one : AdventRunner
{
public:
	virtual void Run(string input) override;
	virtual void Run_2(string input) override;

private:
	bool IsNumber(string s, int* number);
};

