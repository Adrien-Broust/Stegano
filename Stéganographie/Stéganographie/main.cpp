#include "Bits.h"
#include "Files.h"
#include "Message.h"
#include <iostream>

int main()
{
<<<<<<< HEAD
    try
    {
        auto bmp = Files::ReadAll("Apple.bmp");
        std::size_t start = Files::PixelOffset(bmp);

        Message::Embed(bmp, start, "Hello World", "cle"); 
        Files::WriteAll("Apple_stego.bmp", bmp);

}
