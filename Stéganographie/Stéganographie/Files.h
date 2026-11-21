#pragma once
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>
#include <bitset>
#include <cstdint>

class Files
{
private:
    uint32_t offsetPixel;
    uint32_t width;
    uint32_t height;
    size_t stride;
	std::vector<uint32_t> buffer;
public:
    void openFileBmp(const char* file);
    void copyFile(const char* source, const char* destination);
    uint32_t GetoffsetPixel(const char* file);
    uint32_t GetWidth(const char* file);
    uint32_t GetHeight(const char* file);
    size_t GetStride(const char* file);
    uint8_t componantFile(const char* file, uint32_t row, uint32_t column);
    void hideBit(const char* file, int bit);
};

