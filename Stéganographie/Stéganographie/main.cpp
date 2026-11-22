#include "Bits.h"
#include "Files.h"
#include <iostream>

int main()
{
    Files imageApple;
	imageApple.openFileBmp("Apple.bmp");
	imageApple.componantFile("Apple.bmp", 0, 0, 0);
}
