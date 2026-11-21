#include "Files.h"

void Files::openFileBmp(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    size_t buffersize = std::filesystem::file_size(file);
	buffer.resize(buffersize);
    read_file.read(reinterpret_cast<char*>(buffer.data()), buffersize);
    if (buffer[0] != 'B' || buffer[1] != 'M')
    {
        std::cerr << "Erreur : Ce n'est pas un fichier BMP valide.";
    }
    if (buffersize < 54)
    {
        std::cerr << "Erreur : Champs de l'en-tete incorrect";
    }
	width = 
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[18])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[19])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[20])) << 16) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[21])) << 24);
	height =
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[22])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[23])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[24])) << 16) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[25])) << 24);
    offsetPixel = 
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[10])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[11])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[12])) << 16) |
		(static_cast<uint32_t>(static_cast<uint8_t>(buffer[13])) << 24);
	stride = (width * 3 + 3) / 4 * 4;
}

uint32_t Files::GetoffsetPixel(const char* file)
{
    return offsetPixel;
}

uint32_t Files::GetWidth(const char* file)
{
	return width;
}

uint32_t Files::GetHeight(const char* file)
{
	return height;
}

size_t Files::GetStride(const char* file)
{
    return stride;
}

uint8_t Files::componantFile(const char* file, uint32_t row, uint32_t column)
{
    uint32_t componant = 0;
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
    for (uint32_t channel = 0; channel < 3; ++channel)
    {
        if (row >= GetHeight(file) || column >= GetWidth(file))
        {
            throw std::out_of_range("Row or column is out of range");
        }
        std::size_t index = GetoffsetPixel(file) + row * GetStride(file) + column * 3 + channel;
        componant = static_cast<uint8_t>(buffer[index]);
		std::cout << componant << std::endl;
    }
    return componant;
}
    
		

void Files::hideBit(const char* file, int bit)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);

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


