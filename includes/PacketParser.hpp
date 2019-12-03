//
// Created by mhonchar on 03.12.19.
//

#ifndef PACKETPARSER_PACKETPARSER_HPP
# define PACKETPARSER_PACKETPARSER_HPP

# include <iostream>
# include <map>
# include <regex>

enum class valueType {Int, Float, String};


class PacketParser
{
private:
	std::map< std::string, std::pair< valueType, std::string > >	data;

public:
	PacketParser();
	~PacketParser();

	void	beginProcessing(std::istream &is);
	void 	extractData();
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
