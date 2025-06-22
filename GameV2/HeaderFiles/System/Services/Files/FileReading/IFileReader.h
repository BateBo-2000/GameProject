#pragma once
#ifndef I_FILE_READER_H
#define I_FILE_READER_H

#include <string>

class IFileReader {
public:
	virtual ~IFileReader() = default;
	virtual bool readFileContents(std::string& destination) = 0;
};

#endif //I_FILE_READER_H
