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

	while (std::getline(is, packet))
	{

	}

}

//void 	PacketParser::extractData();
//
//
//
//void	PacketParser::readPacket();
//void	PacketParser::splitPacket();
//void	PacketParser::validateSegment();
//void	PacketParser::saveField();
//void	PacketParser::findField();
//void	PacketParser::checkSegmentDataType();
//void	PacketParser::updateField();


