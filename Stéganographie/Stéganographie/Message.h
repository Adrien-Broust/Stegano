#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Files.h"

class Message
{
public:
	static constexpr std::size_t HeaderSize = 9;
	static constexpr unsigned int FlagXor = 0;

	void Embed(Files& image, uint32_t row, uint32_t column,
		uint32_t channel, const std::string& text,
		const std::string& key = "");

	std::string Extract(Files& image, uint32_t row, uint32_t column,
		uint32_t channel, const std::string& key = "");

private:
	static void ApplyXor(std::vector<std::uint8_t>& data, const std::string& key);
};