#include "Bits.h"
#include "Files.h"
#include "Message.h"
#include <iostream>

int main()
{
    try
    {
        auto bmp = Files::ReadAll("Apple.bmp");
        std::size_t start = Files::PixelOffset(bmp);

        Message::Embed(bmp, start, "Hello World", "cle"); // Cette "cle" est la "serrure"
        Files::WriteAll("Apple_stego.bmp", bmp);

        auto loaded = Files::ReadAll("Apple_stego.bmp");
        std::cout << Message::Extract(loaded, Files::PixelOffset(loaded), "cle") << "\n"; // Cette "cle" est la "clé"
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << "\n";
    }
}

