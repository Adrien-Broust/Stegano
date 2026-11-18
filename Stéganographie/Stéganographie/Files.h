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
	static void openFileBmp(const char* file);
	void copyFile(const char* file);
};

