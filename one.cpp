#include "one.h"
#include <cctype>

void one::Run(string input)
{
	vector<string> inputLines = FileReader::SplitStringByNewline(input);
	vector<string> results;

	for (string x : inputLines)
	{
		string result;

		char firstNumberChar = ' ';
		char lastNumberChar = ' ';

		char currentNumberChar = ' ';

		for (char c : x)
		{
			if (isdigit(c))
			{
				if (isblank(firstNumberChar))
				{
					firstNumberChar = c;
				}
				else
				{
					currentNumberChar = c;

					Logger::Log("current character number: ");
					Logger::Log(currentNumberChar);
				}

				lastNumberChar = currentNumberChar;
			}
		}

		if (isblank(lastNumberChar))
		{
			lastNumberChar = firstNumberChar;
		}

		Logger::Log("first character number: ");
		Logger::Log(firstNumberChar);
		Logger::Log("last character number: ");
		Logger::Log(lastNumberChar);

		result += firstNumberChar;
		result += lastNumberChar;

		results.push_back(result);
	}

	uint32_t finalResult = 0;
	
	for (string result : results)
	{
		int number = stoi(result);

		finalResult += number;
	}

	Logger::Log("result: ");
	Logger::Log(finalResult);
}

void one::Run_2(string input)
{
	vector<string> inputLines = FileReader::SplitStringByNewline(input);
	vector<string> results;

	for (string line : inputLines)
	{
		string result;

		char firstNumberChar = ' ';
		char lastNumberChar = ' ';

		char currentNumberChar = ' ';

		Logger::Log(line);

		// Get First
		string builder;
		for (int i = 0; i < line.size(); i++)
		{
			char c = line[i];

			if (isdigit(c))
			{
				firstNumberChar = c;
				break;
			}

			builder += c;
			int numberPtr = 0;

			if (IsNumber(builder, &numberPtr))
			{
				firstNumberChar = '0' + numberPtr;  // Convert single digit number to char

				Logger::Log(firstNumberChar);
				break;
			}
		}
		
		// Get Second
		builder.clear();

		for (int i = line.size() - 1; i >= 0; i--)
		{
			char c = line[i];

			if (isdigit(c))
			{
				lastNumberChar = c;
				break;
			}

			// Add first
			builder = c + builder;
			int numberPtr = 0;

			if (IsNumber(builder, &numberPtr))
			{
				lastNumberChar = '0' + numberPtr;  // Convert single digit number to char
				break;
			}
		}

		if (isblank(lastNumberChar))
		{
			lastNumberChar = firstNumberChar;
		}

		Logger::Log("first character number: ");
		Logger::Log(firstNumberChar);
		Logger::Log("last character number: ");
		Logger::Log(lastNumberChar);

		result += firstNumberChar;
		result += lastNumberChar;

		results.push_back(result);
	}

	uint32_t finalResult = 0;

	for (string result : results)
	{
		int number = stoi(result);

		finalResult += number;
	}

	Logger::Log("result: ");
	Logger::Log(finalResult);
}

bool one::IsNumber(string s, int* number)
{
	if (s.find("one") != string::npos)
	{
		*number = 1;
		return true;
	}
	if (s.find("two") != string::npos)
	{
		*number = 2;
		return true;
	}
	if (s.find("three") != string::npos)
	{
		*number = 3;
		return true;
	}
	if (s.find("four") != string::npos)
	{
		*number = 4;
		return true;
	}
	if (s.find("five") != string::npos)
	{
		*number = 5;
		return true;
	}
	if (s.find("six") != string::npos)
	{
		*number = 6;
		return true;
	}
	if (s.find("seven") != string::npos)
	{
		*number = 7;
		return true;
	}
	if (s.find("eight") != string::npos)
	{
		*number = 8;
		return true;
	}
	if (s.find("nine") != string::npos)
	{
		*number = 9;
		return true;
	}

	return false;
}