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
