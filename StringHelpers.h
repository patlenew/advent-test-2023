#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "Logger.h"

using namespace std;

class StringHelpers
{

public:
	
	static vector<string> Split(const string& s, char delimiter) 
    {
        vector<string> parts;
        string part;
        istringstream tokenStream(s);

        while (getline(tokenStream, part, delimiter)) 
        {
            parts.push_back(part);
        }

        return parts;
    }

    static string Trim(const std::string& str) 
    {
        size_t first = str.find_first_not_of(" \n\r\t");
        size_t last = str.find_last_not_of(" \n\r\t");

        return str.substr(first, (last - first + 1));
    }

    static bool Contains(const string& s, const string& other)
    {
        return s.find(other) != string::npos;
    }

    static bool Contains(const vector<string>& strings, const string& other)
    {
        for (string s : strings)
        {
            if (s.find(other) != string::npos)
            {
                DEBUG_LOG_1("found s ", s);
                DEBUG_LOG_1("with other ", other);

                return true;
            }
        }

        return false;
    }

    static bool IsNumber(const string& s)
    {
        for (char const& c : s)
        {
            if (!std::isdigit(c)) return false;
        }

        return true;
    }

    static vector<string> ExtractNumberStringsFromLine(const string& line)
    {
        vector<string> allNumberStrings;
        string currentNumberString;

        for (const char& c : line)
        {
            if (std::isdigit(c))
            {
                currentNumberString += c;
            }
            else if (!currentNumberString.empty())
            {
                // Copy
                string toInsert = currentNumberString;

                allNumberStrings.push_back(toInsert);

                // Clear
                currentNumberString = "";
            }
        }

        // Last number
        if (!currentNumberString.empty())
        {
            // Copy
            string toInsert = currentNumberString;

            allNumberStrings.push_back(currentNumberString);
        }

        return allNumberStrings;
    }

    static vector<uint32_t> ExtractUint32FromLine(const string& line)
    {
        vector<uint32_t> allNumberStrings;
        string currentNumberString;

        for (const char& c : line)
        {
            if (std::isdigit(c))
            {
                currentNumberString += c;
            }
            else if (!currentNumberString.empty())
            {
                // Copy
                uint32_t number = std::stoul(currentNumberString, nullptr, 0);

                allNumberStrings.push_back(number);

                // Clear
                currentNumberString = "";
            }
        }

        // Last number
        if (!currentNumberString.empty())
        {
            // Copy
            uint32_t number = std::stoul(currentNumberString, nullptr, 0);

            allNumberStrings.push_back(number);
        }

        return allNumberStrings;
    }
};

