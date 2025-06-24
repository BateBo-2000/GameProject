#pragma once
#ifndef TEXT_FILE_READER
#define TEXT_FILE_READER

#include "IFileReader.h"
#include <string>


class TextFileReader : public ITextFileReader {
public:
	~TextFileReader() override = default;
	bool readFileContents(const std::string& path, std::string& destination) override;
};


#endif // ! TEXT_FILE_READER
