#pragma once
#ifndef I_FILE_READER_H
#define I_FILE_READER_H

#include <string>

class ITextFileReader {
public:
	virtual ~ITextFileReader() = default;
	virtual bool readFileContents(const std::string& path, std::string& destination) = 0;
};

#endif //I_FILE_READER_H
