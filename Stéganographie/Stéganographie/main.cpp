#include "Bits.h"
#include "Files.h"
#include "Message.h"
#include <iostream>

int main()
{
	Files imageApple;
	imageApple.openFileBmp("Apple.bmp");

	Message message;

	message.Embed(imageApple, 0, 0, 0, "Bonjour", "Poire");

	std::string result = message.Extract(imageApple, 0, 0, 0, "Poire");

	std::cout << result << std::endl;
}
