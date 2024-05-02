#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include "Logger.h"

using namespace std;

class FileReader
{
public:
	string GetFileContent(string path);

    static vector<string> SplitStringByNewline(const string& str) 
    {
        vector<string> result;
        stringstream ss(str);
        string line;

        while (getline(ss, line)) {
            result.push_back(line);
        }

        return result;
    }

    static char** SplitStringBy2DGrid(const string& str, int& n, int& m)
    {
        vector<string> lines = SplitStringByNewline(str);
        n = lines.size();
        m = lines[0].size();

        DEBUG_LOG_1("n : ", n);
        DEBUG_LOG_1("m : ", m);

        char** result = new char*[n];
        
        for (int i = 0; i < n; i++) {

            // Declare a memory block
            // of size n
            result[i] = new char[m];
        }

        for (int i = 0; i < n; i++) 
        {
            string current;

            for (int j = 0; j < m; j++) 
            {
                result[i][j] = lines[i][j];

                current += result[i][j];
            }

            //DEBUG_LOG(current);
        }

        return result;
    }
};

