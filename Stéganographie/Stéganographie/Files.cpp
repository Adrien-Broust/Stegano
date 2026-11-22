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
	width = buffer[18] | buffer[19] << 8 | buffer[20] << 16 | buffer[21] << 24;
	height =buffer[22] | buffer[23] << 8 | buffer[24] << 16 | buffer[25] << 24;
    offsetPixel = buffer[10] | buffer[11] << 8 | buffer[12] << 16 | buffer[13] << 24;
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

uint8_t Files::componantFile(uint32_t row, uint32_t column, uint32_t channel)
{
    if (row >= height || column >= width || channel >= 3)
    {
        throw std::out_of_range("Pixel invalide");
    }
    uint32_t bmpRow = 0;
    if (height > 0)
    {
        bmpRow = height - 1 - row;
    }
    else
    {
        bmpRow = row;
    }
    size_t index = offsetPixel + bmpRow * stride + column * 3 + channel;
    return buffer[index];
}

void Files::hideBit(uint32_t row, uint32_t column, uint32_t channel, uint8_t bit)
{
	uint8_t pixelValue = componantFile(row, column, channel);
	pixelValue = (pixelValue & 0xFEu) | bit;
    uint32_t bmpRow = 0;
    if (height > 0)
    {
        bmpRow = height - 1 - row;
    }
    else
    {
        bmpRow = row;
    }
    size_t index = offsetPixel + bmpRow * stride + column * 3 + channel;
	buffer[index] = pixelValue;
}

void Files::hideOctet(uint32_t row, uint32_t column, uint32_t channel, uint8_t octet)
{
    for (int i = 0; i < 8; ++i)
    {
        uint8_t bit = (octet >> (7 - i)) & 1;
        hideBit(row, column, channel, bit);
        ++column;
        if (column >= width)
        {
            column = 0;
            ++row;
            if (row >= std::abs(height))
            {
                std::cerr << "Erreur : pas assez de place pour cacher l'octet";
            }
        }
    }
}

uint8_t Files::extractBit(uint32_t row, uint32_t column, uint32_t channel)
{
    uint8_t pixelValue = componantFile(row, column, channel);
    return pixelValue & 1u;
}

uint8_t Files::extractOctet(uint32_t row, uint32_t column, uint32_t channel)
{
    uint8_t octet = 0;
    for (int i = 0; i < 8; ++i)
    {
        uint8_t bit = extractBit(row, column, channel);
        octet = (octet << 1) | bit;
        ++column;
        if (column >= width)
        {
            column = 0;
            ++row;
            if (row >= std::abs(height))
            {
                std::cerr << "Erreur : pas assez de place pour extraire l'octet";
            }
        }
    }
    return octet;
}
void Files::WriteBytes(uint32_t row, uint32_t column, uint32_t channel, const std::vector<uint8_t>& bytes)
{
	uint32_t absHeight = std::abs(height);
    size_t start = row * width + column;
    size_t capacity = width * absHeight;
    size_t totalBits = bytes.size() * 8;

    if (start > capacity || totalBits > capacity - start)
        throw std::out_of_range("Image trop petite");

    for (size_t i = 0; i < bytes.size(); ++i)
    {
        for (int b = 0; b < 8; ++b)
        {
            uint8_t bit = (bytes[i] >> (7 - b)) & 1;

            size_t pos = start + i * 8 + b;

            uint32_t currentRow = pos / width;
            uint32_t currentColumn = pos % width;

            hideBit(currentRow, currentColumn, channel, bit);
        }
    }
}

std::vector<uint8_t> Files::ReadBytes(uint32_t row, uint32_t column, uint32_t channel, size_t count)
{
	uint32_t absHeight = std::abs(height);
    size_t start = row * width + column;
    size_t capacity = width * absHeight;
    size_t totalBits = count * 8;

    if (start > capacity || totalBits > capacity - start)
        throw std::out_of_range("Image trop petite");

    std::vector<uint8_t> result(count, 0);

    for (size_t i = 0; i < count; ++i)
    {
        for (int b = 0; b < 8; ++b)
        {
            size_t pos = start + i * 8 + b;

            uint32_t currentRow = pos / width;
            uint32_t currentColumn = pos % width;

            uint8_t bit = extractBit(currentRow, currentColumn, channel);

            result[i] = (result[i] << 1) | bit;
        }
    }
    return result;
}


void Files::WriteAll(const char* file, const std::vector<std::uint8_t>& data)
{
    std::ofstream out(file, std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error("Cannot write file");
    out.write(reinterpret_cast<const char*>(data.data()),
        static_cast<std::streamsize>(data.size()));
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


