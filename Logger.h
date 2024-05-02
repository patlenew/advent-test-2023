#pragma once

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

#define DEBUG_LOG(text) std::cout << text << std::endl;
#define DEBUG_LOG_1(text, param1) std::cout << text << param1 << std::endl;

class Logger
{
public:

	template <typename T>
	static void Log(const T& value)
	{
		stringstream ss;
		ss << value;
		cout << ss.str() << endl;
	}
};

