#include "Files.h"

void Files::openFileBmp(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);

    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    constexpr std::size_t buffer_size = 500;
    char buffer[buffer_size];
    
    read_file.read(buffer, 14);

    if (buffer[0] != 'B' || buffer[1] != 'M')
    {
        std::cout << "Erreur : Ce n'est pas un fichier BMP valide.";
    }

    if (buffer[13] != '(')
    {
        std::cout << "Erreur : Champs de l'en-tête incorrect";
    }

    std::streamsize bytes_read = read_file.gcount();

    std::string result(
        buffer,
        static_cast<std::size_t>(bytes_read)
    );
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

std::uint32_t Files::PixelOffset(const std::vector<std::uint8_t>& bmp)
{
    return  std::uint32_t(bmp[10])
        | (std::uint32_t(bmp[11]) << 8)
        | (std::uint32_t(bmp[12]) << 16)
        | (std::uint32_t(bmp[13]) << 24);
}
