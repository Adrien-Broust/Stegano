#pragma once
#include <vector>
#include <cstdint>
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
    int32_t height;
    size_t stride;
	std::vector<uint8_t> buffer;
public:
    void openFileBmp(const char* file);
    void copyFile(const char* source, const char* destination);
    uint32_t GetoffsetPixel(const char* file);
    uint32_t GetWidth(const char* file);
    int32_t GetHeight(const char* file);
    size_t GetStride(const char* file);
    uint8_t componantFile(uint32_t row, uint32_t column, uint32_t channel);
	void hideBit(uint32_t row, uint32_t column, uint32_t channel, uint8_t bit);
	void hideOctet(uint32_t row, uint32_t column, uint32_t channel, uint8_t octet);
	uint8_t extractBit(uint32_t row, uint32_t column, uint32_t channel);
	uint8_t extractOctet(uint32_t row, uint32_t column, uint32_t channel);
    void WriteBytes(uint32_t row, uint32_t column, uint32_t channel,const std::vector<uint8_t>& bytes);
    std::vector<uint8_t> ReadBytes(uint32_t row, uint32_t column,uint32_t channel, size_t count);
	std::vector<std::uint8_t> ReadAll(const char* file);
	void WriteAll(const char* file, const std::vector<std::uint8_t>& data);
};

