//
// Created by mhonchar on 03.12.19.
//

#ifndef PACKETPARSER_PACKETPARSER_HPP
#define PACKETPARSER_PACKETPARSER_HPP

#include <iostream>

class PacketParser
{
private:
	std::istream	m_dataStream;
public:
	PacketParser();
	~PacketParser();
	void	bindStream(std::istream &is);
	void	beginProcessing();

private:
	void	readPacket();
	void	splitPacket();
	void	validateSegment();
	void	saveField();
	void	findField();
	void	checkSegmentDataType();
	void	updateField();
};


#endif //PACKETPARSER_PACKETPARSER_HPP
