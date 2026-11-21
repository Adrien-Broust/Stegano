#include "Files.h"

void Files::openFileBmp(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);
    if (buffer[0] != 'B' || buffer[1] != 'M')
    {
        std::cerr << "Erreur : Ce n'est pas un fichier BMP valide.";
    }
    if (buffer[14] != '(' && buffer[15,16,17,18] != 0)
    {
        std::cerr << "Erreur : Champs de l'en-tete incorrect";
    }
}

uint32_t Files::GetoffsetPixel(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);
	uint32_t pixelOffset = 
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[10])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[11])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[12])) << 16) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[13])) << 24);
    return pixelOffset;
}

uint32_t Files::GetWidth(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
	std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);
    uint32_t width = 
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[18])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[19])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[20])) << 16) |
		(static_cast<uint32_t>(static_cast<uint8_t>(buffer[21])) << 24);
	return width;
}

uint32_t Files::GetHeight(const char* file)
{
	std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
	read_file.read(buffer.data(), buffersize);
    uint32_t height = 
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[22])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[23])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[24])) << 16) |
		(static_cast<uint32_t>(static_cast<uint8_t>(buffer[25])) << 24);
	return height;
}

size_t Files::GetStride(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);
    uint32_t width =
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[18])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[19])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[20])) << 16) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[21])) << 24);
    std::size_t stride = (width * 3 + 3) / 4 * 4;
    return stride;
}

void Files::composanteFile(const char* file)
{
	std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
	}
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);
    if (GetHeight(file) <= 0 || GetWidth(file) <= 0)
    {
        throw std::runtime_error("Invalid image dimensions");
	}
    for (uint32_t row = 0; row < GetHeight(file); ++row)
    {
        for (uint32_t column = 0; column < GetWidth(file); ++column)
        {
            for (int channel = 0; channel < 3; ++channel)
            {
				std::size_t index = GetoffsetPixel(file) + row * GetStride(file) + column * 3 + channel;
				uint32_t composante = static_cast<uint8_t>(buffer[index]);
			}
        }
    }
}

void Files::copyFile(const char* file, const char* fileCopy)
{
	std::ifstream origin(file, std::ios::binary);
	if (!origin.is_open())
	{
		throw std::runtime_error("Cannot open file");
	}
	std::ofstream copy(fileCopy, std::ios::binary);
	if (!copy.is_open())
	{
		throw std::runtime_error("Cannot open copy file");
	}
	copy << origin.rdbuf();
}


