#include "FileReader.h"
#include <iostream>
#include <fstream>

string FileReader::GetFileContent(string path)
{
    fstream file;
    file.open(path, ios::in);

    string output;
    string fileOutput;
    while (getline(file, output))
    {
        fileOutput.append(output);
        fileOutput.append("\n");
    }

    return fileOutput;
}
