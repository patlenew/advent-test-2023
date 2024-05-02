#include "five.h"
#include "StringHelpers.h"
#include <utility>

enum ToTypes
{
	None = 0,

	ToSoil = 1,
	ToFertilizer = 2,
	ToWater = 3,
	ToLight = 4,
	ToTemperature = 5,
	ToHumidity = 6,
	ToLocation = 7,

	End = 8,
};

constexpr ToTypes operator++(ToTypes& a, int) 
{
	int i = static_cast<std::underlying_type_t<ToTypes>>(a);

	i += 1;

	a = static_cast<ToTypes>(i);
	return a;
}

struct Range
{
	uint32_t source;
	uint32_t destination;
	uint32_t range;
};

void Parse(vector<string> lines);
void AddToRange(vector<Range>& ranges, const string& line);
void PrintRange(Range& range);
bool TryFindRange(const uint32_t& sourceNumber, const vector<Range>& ranges, Range& chosenRange);
vector<Range> GetCurrentRanges(ToTypes type);

vector<uint32_t> seeds;

vector<Range> seedToSoilRanges;
vector<Range> soilToFertilizerRanges;
vector<Range> fertilizerToWaterRanges;
vector<Range> waterToLightRanges;
vector<Range> lightToTemperatureRanges;
vector<Range> temperatureToHumidityRanges;
vector<Range> humidityToLocationRanges;

void five::Run(string input)
{
	vector<string> lines = FileReader::SplitStringByNewline(input);

	Parse(lines);

	uint32_t lowest = UINT32_MAX;

	for (size_t i = 0; i < 2000000000; i++)
	{
		lowest = i;
	}

	lowest = UINT32_MAX;

	for (uint32_t seed : seeds)
	{
		uint32_t currentNumber = seed;
		ToTypes currentNextType = ToSoil;
		Range chosenRange;
		
		while (currentNextType != End)
		{
			// otherwise, keep same number
			if (TryFindRange(currentNumber, GetCurrentRanges(currentNextType), chosenRange))
			{
				uint32_t diff = currentNumber - chosenRange.source;
				currentNumber = chosenRange.destination + diff;
			}

			if (currentNumber < lowest && currentNextType == ToLocation)
			{
				lowest = currentNumber;
			}
			
			currentNextType++;
		}

	}

	DEBUG_LOG_1("Lowest: ", lowest);
}

void five::Run_2(string input)
{
}

void Parse(vector<string> lines)
{
	ToTypes currentType = None;
	bool preparedNextData = false;

	for (int i = 0; i < lines.size(); i++)
	{
		string line = lines[i];

		// first: seeds
		if (i == 0)
		{
			seeds = StringHelpers::ExtractUint32FromLine(line);
			continue;
		}

		// Skip the header
		if (preparedNextData)
		{
			preparedNextData = false;
			continue;
		}

		// Prepare for next line
		if (line.empty())
		{
			currentType++;
			preparedNextData = true;

			continue;
		}
		else
		{
			switch (currentType)
			{
			case ToSoil:
				AddToRange(seedToSoilRanges, line);
				break;

			case ToFertilizer:
				AddToRange(soilToFertilizerRanges, line);
				break;

			case ToWater:
				AddToRange(fertilizerToWaterRanges, line);
				break;

			case ToLight:
				AddToRange(waterToLightRanges, line);
				break;

			case ToTemperature:
				AddToRange(lightToTemperatureRanges, line);
				break;

			case ToHumidity:
				AddToRange(temperatureToHumidityRanges, line);
				break;

			case ToLocation:
				AddToRange(humidityToLocationRanges, line);
				break;

			default:
				break;
			}
		}
	}
}

void AddToRange(vector<Range>& ranges, const string& line)
{
	Range range;
	vector<uint32_t> numbers = StringHelpers::ExtractUint32FromLine(line);

	for (int i = 0; i < numbers.size(); i++)
	{
		// Destination
		if (i == 0)
		{
			range.destination = numbers[i];
		}

		// Source 
		if (i == 1)
		{
			range.source = numbers[i];
		}

		// Range
		if (i == 2)
		{
			range.range = numbers[i];
		}
	}

	ranges.push_back(range);
}

bool TryFindRange(const uint32_t& sourceNumber, const vector<Range>& ranges, Range& chosenRange)
{
	for (Range range : ranges)
	{
		uint32_t max = range.source + range.range;

		if (sourceNumber <= max && sourceNumber >= range.source)
		{
			chosenRange = range;
			return true;
		}
	}

	return false;
}

vector<Range> GetCurrentRanges(ToTypes type)
{
	switch (type)
	{
		case ToSoil:
			return seedToSoilRanges;
		case ToFertilizer:
			return soilToFertilizerRanges;
		case ToWater:
			return fertilizerToWaterRanges;
		case ToLight:
			return waterToLightRanges;
		case ToTemperature:
			return lightToTemperatureRanges;
		case ToHumidity:
			return temperatureToHumidityRanges;
		case ToLocation:
			return humidityToLocationRanges;
	}

	return vector<Range>();
}

void PrintRange(Range& range)
{
	DEBUG_LOG_1("Source: ", range.source);
	DEBUG_LOG_1("Destination: ", range.destination);
	DEBUG_LOG_1("Range: ", range.range);
}
