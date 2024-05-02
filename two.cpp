#include "two.h"
#include "StringHelpers.h"

struct GameContent
{
	int greenCount;
	int blueCount;
	int redCount;

	void Log()
	{
		cout << "Green: " << greenCount << ", Blue: " << blueCount << ", Red: " << redCount << endl;
	}
};

bool IsValidGame(GameContent game);
int GetGamePower(vector<GameContent> games);
void ParseGame(string line, int* gameId, vector<GameContent>* games);
string GetNumberString(string line, int pos, int offset);


void two::Run(string input)
{
	vector<string> inputLines = FileReader::SplitStringByNewline(input);

	int sum = 0;

	for (string line : inputLines)
	{
		int gameNumber = 0;
		vector<GameContent> content;

		ParseGame(line, &gameNumber, &content);

		bool valid = false;

		for (GameContent game : content)
		{
			valid = IsValidGame(game);

			if (!valid)
			{
				break;
			}
		}

		if (valid)
		{
			sum += gameNumber;
		}
	}

	Logger::Log("Valid Game Number Sum:");
	Logger::Log(sum);
}

bool IsValidGame(GameContent game)
{
	int validRedCount = 12;
	int validGreenCount = 13;
	int validBlueCount = 14;

	if (game.redCount > validRedCount)
	{
		return false;
	}
	
	if (game.blueCount > validBlueCount)
	{
		return false;
	}

	if (game.greenCount > validGreenCount)
	{
		return false;
	}

	return true;
}


void ParseGame(string line, int* gameId, vector<GameContent>* games)
{
	char delimiterNumber = ':';
	char delimiterGameContent = ';';

	size_t colonPos = line.find(":");
	string numberString;

	for (size_t i = colonPos - 1; i >= 0; i--)
	{
		if (!isdigit(line[i]))
		{
			break;
		}

		char digit = line[i];
		string digitString;
		digitString += digit;

		numberString.insert(0, digitString);
	}

	*gameId = stoi(numberString);

	string trimmedLine = StringHelpers::Trim(line);
	vector<string> splitLine = StringHelpers::Split(trimmedLine, delimiterGameContent);

	for(string part : splitLine)
	{
		size_t redPos = part.find("red");
		size_t greenPos = part.find("green");
		size_t bluePos = part.find("blue");

		GameContent content;
		content.redCount = 0;
		content.blueCount = 0;
		content.greenCount = 0;

		if (redPos != string::npos)
		{
			string redNumber = GetNumberString(part, redPos, 1);
			content.redCount = stoi(redNumber);
		}

		if (greenPos != string::npos)
		{
			string greenNumber = GetNumberString(part, greenPos, 1);
			content.greenCount = stoi(greenNumber);
		}

		if (bluePos != string::npos)
		{
			string blueNumber = GetNumberString(part, bluePos, 1);
			content.blueCount = stoi(blueNumber);
		}

		games->push_back(content);
	}
}

string GetNumberString(string line, int pos, int offset)
{
	string numberString;

	for (size_t i = pos - 1 - offset; i >= 0; i--)
	{
		if (!isdigit(line[i]))
		{
			break;
		}

		char digit = line[i];
		string digitString;
		digitString += digit;

		numberString.insert(0, digitString);
	}

	return numberString;
}

void two::Run_2(string input)
{
	vector<string> inputLines = FileReader::SplitStringByNewline(input);

	int sum = 0;

	for (string line : inputLines)
	{
		int gameNumber = 0;
		vector<GameContent> content;

		ParseGame(line, &gameNumber, &content);

		int power = GetGamePower(content);

		sum += power;
	}

	Logger::Log("Power Sum:");
	Logger::Log(sum);
}

int GetGamePower(vector<GameContent> games)
{
	int maxRed = 0;
	int maxGreen = 0;
	int maxBlue = 0;

	for (GameContent game : games)
	{
		maxRed = game.redCount > maxRed ? game.redCount : maxRed;
		maxGreen = game.greenCount > maxGreen ? game.greenCount : maxGreen;
		maxBlue = game.blueCount > maxBlue ? game.blueCount : maxBlue;
	}

	return maxRed * maxGreen * maxBlue;
}
