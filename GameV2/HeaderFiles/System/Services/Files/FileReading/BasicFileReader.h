#pragma once
#ifndef TEXT_FILE_READER
#define TEXT_FILE_READER

#include "IFileReader.h"
#include <string>


class TextFileReader : public IFileReader {
public:
	TextFileReader(const std::string& path);
	bool readFileContents(std::string& destination) override;

private:
	std::string path;
};


#endif // ! TEXT_FILE_READER
