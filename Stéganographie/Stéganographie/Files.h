#pragma once
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class Files
{
public:
	void openFileBmp(const char* file);
	std::vector<std::uint8_t> ReadAll(const char* file);
	void WriteAll(const char* file, const std::vector<std::uint8_t>& data);
};

