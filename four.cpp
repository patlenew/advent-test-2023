#include "four.h"
#include "StringHelpers.h"
#include <map>

map<int, int> cardMap;

void four::Run(string input)
{
	vector<string> inputLines = FileReader::SplitStringByNewline(input);

	int result = 0;

	for (string line : inputLines)
	{
		vector<string> removedCardStrings = StringHelpers::Split(line, ':');
		string removedCardString = removedCardStrings[1];

		vector<string> numbers = StringHelpers::Split(removedCardString, '|');

		vector<string> winningNumbers = StringHelpers::Split(numbers[0], ' ');
		vector<string> currentNumbers = StringHelpers::Split(numbers[1], ' ');

		int value = 2;
		int power = 0;
		int currentResult = 0;

		for (string currentNumber : currentNumbers)
		{
			// currentNumber = StringHelpers::Trim(currentNumber);

			if (currentNumber.empty()) continue;

			for (string winningNumber : winningNumbers)
			{
				if (winningNumber.empty()) continue;

				int currentRealNumber = stoi(currentNumber);
				int winningRealNumber = stoi(winningNumber);

				if (currentRealNumber == winningRealNumber)
				{
					currentResult = pow(value, power++);

					// DEBUG_LOG_1("currentResult ", currentResult);
				}
			}
		}

		result += currentResult;
	}

	DEBUG_LOG(result);
}

void four::Run_2(string input)
{
	vector<string> inputLines = FileReader::SplitStringByNewline(input);

	int result = 0;
	int cardId = 1;

	for (string line : inputLines)
	{
		vector<string> removedCardStrings = StringHelpers::Split(line, ':');
		string removedCardString = removedCardStrings[1];

		vector<string> numbers = StringHelpers::Split(removedCardString, '|');

		vector<string> winningNumbers = StringHelpers::Split(numbers[0], ' ');
		vector<string> currentNumbers = StringHelpers::Split(numbers[1], ' ');

		// One copy of the current card
		cardMap[cardId] += 1;
		
		// Times to process current card
		int nextCardId = cardId + 1;

		for (string currentNumber : currentNumbers)
		{
			if (currentNumber.empty()) continue;

			for (string winningNumber : winningNumbers)
			{
				if (winningNumber.empty()) continue;

				int currentRealNumber = stoi(currentNumber);
				int winningRealNumber = stoi(winningNumber);

				if (currentRealNumber == winningRealNumber)
				{
					cardMap[nextCardId++] += cardMap[cardId];
				}
			}
		}

		cardId++;
	}

	for (std::pair<int, int> numberPair : cardMap)
	{
		result += numberPair.second;
	}

	DEBUG_LOG(result);
}
