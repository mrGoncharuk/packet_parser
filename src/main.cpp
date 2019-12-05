#include <iostream>
#include <fstream>

#include "../includes/PacketParser.hpp"

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: " <<argv[0] << " [filename]\n";
		return 0;
	}

	std::ifstream ifs(argv[1]);
	if (!ifs.is_open())
	{
		std::cout << "Can't reach '" << argv[1] << "'. Ensure that file exists.\n";
		return (0);
	}

	PacketParser parser;
	try
	{
		parser.beginProcessing(ifs);
		parser.showData();
	}
	catch (KeyValueNotFoundException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (UnsupportedKeyValueException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (BadExspressionException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (ReDefinitionException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (UnrecognizedElementException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (ModifyingBeforeInitializationException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (BadTypeException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (UnsupportedOperationException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
