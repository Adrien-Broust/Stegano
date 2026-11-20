#pragma once
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>

class Files
{
public:
    static void openFileBmp(const char* filename);
    static void copyFile(const char* source, const char* destination);
	static void compareFiles(const char* file1, const char* file2);
    int offsetPixel(const char* file);
};

