#include <iostream>
#include <fstream>

#include "../includes/PacketParser.hpp"

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./packparsley [filename]\n";
		return 0;
	}

	std::ifstream ifs(argv[1]);
	if (!ifs.is_open())
	{
		std::cout << "Can't reach '" << argv[1] << "'. Ensure that file exists.\n";
		return (0);
	}

	PacketParser parser;
	parser.beginProcessing(ifs);

	return 0;
}
