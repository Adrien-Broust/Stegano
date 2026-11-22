#include "Files.h"

void Files::openFileBmp(const char* file)
{

}
std::vector<std::uint8_t> Files::ReadAll(const char* file)
{
    std::ifstream in(file, std::ios::binary);
    if (!in.is_open())
        throw std::runtime_error("Cannot open file");

    std::vector<std::uint8_t> data(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    if (data.size() < 54 || data[0] != 'B' || data[1] != 'M')
        throw std::runtime_error("Pas un BMP valide");

    return data;
}

void Files::WriteAll(const char* file, const std::vector<std::uint8_t>& data)
{
    std::ofstream out(file, std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error("Cannot write file");

    out.write(reinterpret_cast<const char*>(data.data()),
        static_cast<std::streamsize>(data.size()));
}
