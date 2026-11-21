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
public:
    static void openFileBmp(const char* filename);
    static void copyFile(const char* source, const char* destination);
    static uint8_t GetoffsetPixel(const char* file);
    static size_t GetStride(const char* file);
};

