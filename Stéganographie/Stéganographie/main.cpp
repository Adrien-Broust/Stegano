#include "Bits.h"
#include "Files.h"
#include <iostream>

int main()
{
    Files imageApple;
	imageApple.openFileBmp("Apple.bmp");
	imageApple.componantFile(0, 0, 0);
	imageApple.hideOctet(568, 169, 2, 'A');
	std::cout << static_cast<int>(imageApple.extractOctet(568, 169, 2)) << std::endl;

}
