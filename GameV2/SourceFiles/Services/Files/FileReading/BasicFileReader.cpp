#include "../../HeaderFiles/System/Services/Files/FileReading/BasicFileReader.h"

#include <fstream>

TextFileReader::TextFileReader(const std::string& path) : path(path)
{}

bool TextFileReader::readFileContents(std::string& destination)
{
    std::ifstream in(path, std::ios::in);
    if (!in) {
        return false;  // could not open
    }

    destination.clear();
    std::string line;

    while (std::getline(in, line)) {
        destination += line;
        if (!in.eof())
            destination += '\n';
    }

    if (in.bad()) return false;
    return true;
}
