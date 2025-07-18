#include "../../HeaderFiles/System/Services/Files/FileReading/BasicFileReader.h"

#include <fstream>

bool TextFileReader::readFileContents(const std::string& path, std::string& destination)
{
    std::ifstream in(path, std::ios::in);
    if (!in) {
        return false;
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
