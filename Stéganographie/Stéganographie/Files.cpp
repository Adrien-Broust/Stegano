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

int Files::offsetPixel(const char* file)
{
    std::ifstream read_file(file, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    read_file.seekg(9, std::ios::beg);
    int pixelOffset = read_file.tellg();
    return pixelOffset;
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
//    f1.seekg(0, std::ios::end);
//    f2.seekg(0, std::ios::end);
//    if (f1.tellg() != f2.tellg())
//    {
//        std::cerr << "Files are different sizes." << std::endl;
//        return;
//    }
//	f1.seekg(0, std::ios::beg);
//	f2.seekg(0, std::ios::beg);
//    
//}