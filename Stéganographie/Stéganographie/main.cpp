#include "Bits.h"
#include "Files.h"
#include <iostream>

int main()
{
    Files imageApple;
	imageApple.openFileBmp("Apple.bmp");
	imageApple.componantFile(0, 0, 0);
	imageApple.hideOctet(0, 0, 0, 12);
}
