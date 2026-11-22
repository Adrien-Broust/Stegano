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
	static void openFileBmp(const char* file);
	static std::vector<std::uint8_t> ReadAll(const char* file);
	static void WriteAll(const char* file, const std::vector<std::uint8_t>& data);
};

