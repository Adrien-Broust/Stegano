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

uint8_t Files::GetoffsetPixel(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    const size_t buffersize = std::filesystem::file_size(file);
    std::vector<char> buffer(buffersize);
    read_file.read(buffer.data(), buffersize);
    uint32_t pixelOffset = buffer[0] << 10 | buffer[1] << 10 | buffer[2] << 10 | buffer[3] << 10;
    std::cout << pixelOffset;
    return pixelOffset;
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
    uint32_t witdh = buffer[0] << 17 | buffer[1] << 17 | buffer[2] << 17 | buffer[3] << 17;
    std::size_t stride = (witdh * 3 + 3) / 4 * 4;
    std::cout << std::dec << +stride;
    return stride;
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

//void Files::compareFiles(const char* file1, const char* file2)
//{
//    std::ifstream f1(file1, std::ios::binary);
//    std::ifstream f2(file2, std::ios::binary);
//    if (!f1.is_open() || !f2.is_open())
//    {
//        throw std::runtime_error("Cannot open file");
//    }
//    
//}
