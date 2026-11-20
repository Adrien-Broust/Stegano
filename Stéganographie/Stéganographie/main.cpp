#include "Bits.h"
#include "Files.h"
#include <iostream>

enum Row
{
    bleu,
    vert,
    rouge,
};

int main()
{
    Files::copyFile("Apple.bmp", "Apple_copy.bmp");
	Files::compareFiles("Apple.bmp", "Apple_copy.bmp");
}
