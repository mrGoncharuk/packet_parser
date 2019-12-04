//
// Created by mhonchar on 03.12.19.
//

#include "../includes/PacketParser.hpp"


PacketParser::PacketParser()
{}
PacketParser::~PacketParser()
{}

void	PacketParser::beginProcessing(std::istream &is)
{
	std::string packet;
	std::regex packet_split("((([\\S]|[\\S][\\S])(?=([^\\\"]*\\\"[^\\\"]*\\\"))\\\"[^\\\"]*\\\"|'[^']*'|[\\S]+)+)");
	std::smatch matches;


	while (std::getline(is, packet))
	{
		std::sregex_iterator  currMatch(packet.begin(), packet.end(), packet_split);	// splitting packet by spaces
		std::sregex_iterator lastMatch;
		while (currMatch != lastMatch)
		{
			std::smatch match = *currMatch;
//			std::cout << match.str() << std::endl;
			processSegment(match.str());
			currMatch++;
		}

	}

}

void	PacketParser::processSegment(std::string seg)
{
	if (seg.find(':') != std::string::npos)
	{
		saveField(seg);
	}
	else
	{
		updateField(seg);
	}
}

//void 	PacketParser::extractData();
//
//
//
//void	PacketParser::readPacket();
//void	PacketParser::splitPacket();
//void	PacketParser::validateSegment();
void	PacketParser::saveField(std::string &seg)
{
	if (seg.length() < 3)
		throw "BadField";
	if (data.find(seg[0]) != data.end())
		throw "Redefinition of element";

	size_t quote_start = seg.find('"');
	std::string field_name;
	if (quote_start != std::string::npos)
		field_name = seg.substr(quote_start, seg.length() - 1);
	else
		field_name = seg.substr(2, seg.length());
	data[seg[0]].first = field_name;

//	std::cout << "Char: " << seg[0] << "\tName: " << field_name << "\n";
}
//void	PacketParser::findField();
//void	PacketParser::checkSegmentDataType();
void	PacketParser::updateField(std::string &seg)
{

}


