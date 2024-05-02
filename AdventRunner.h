#pragma once

#include <string>
#include <vector>
#include "FileReader.h"
#include "Logger.h"

using namespace std;

class AdventRunner
{

public:
	virtual void Run(string input);
	virtual void Run_2(string input);
};

