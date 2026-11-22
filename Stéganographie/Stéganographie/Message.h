#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Message
{
public:
	static constexpr std::size_t HeaderSize = 9;
	static constexpr unsigned int FlagXor = 0;

	static void Embed(std::vector<std::uint8_t>& carrier, std::size_t start,
		const std::string& text, const std::string& key = "");

	static std::string Extract(const std::vector<std::uint8_t>& carrier,
		std::size_t start, const std::string& key = "");

private:
	static void ApplyXor(std::vector<std::uint8_t>& data, const std::string& key);
	static void WriteBytes(std::vector<std::uint8_t>& carrier, std::size_t start,
		const std::vector<std::uint8_t>& bytes);
	static std::vector<std::uint8_t> ReadBytes(const std::vector<std::uint8_t>& carrier,
		std::size_t start, std::size_t count);
};