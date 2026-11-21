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
    static uint32_t GetoffsetPixel(const char* file);
	static uint32_t GetWidth(const char* file);
	static uint32_t GetHeight(const char* file);
    static size_t GetStride(const char* file);
    void composanteFile(const char* file);
};

