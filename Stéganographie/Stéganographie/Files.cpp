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
        std::cerr << "Erreur : Ce n'est pas un fichier BMP";
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
	uint32_t tempHeight =
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[22])) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[23])) << 8) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[24])) << 16) |
        (static_cast<uint32_t>(static_cast<uint8_t>(buffer[25])) << 24);
    height = static_cast<int32_t>(tempHeight);
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

int32_t Files::GetHeight(const char* file)
{
	return height;
}

size_t Files::GetStride(const char* file)
{
    return stride;
}

uint8_t Files::componantFile(const char* file, uint32_t row, uint32_t column, uint32_t channel)
{
    if (row >= height || column >= width || channel >= 3)
    {
        throw std::out_of_range("Pixel invalide");
    }

    uint32_t bmpRow;

    if (height > 0)
    {
        bmpRow = height - 1 - row;
    }
    else
    {
        bmpRow = row;
    }

    size_t index = offsetPixel + bmpRow * stride + column * 3 + channel;
	std::cout << "Colonne: " << column << ", Ligne: " << bmpRow << ", Canal: " << channel << std::endl;
    std::cout << "Index: " << buffer[index] << std::endl;
    return buffer[index];
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


