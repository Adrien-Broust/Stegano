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
