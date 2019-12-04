//
// Created by mhonchar on 03.12.19.
//

#ifndef PACKETPARSER_PACKETPARSER_HPP
# define PACKETPARSER_PACKETPARSER_HPP

# include <iostream>
# include <map>
# include <regex>
# include <sstream>
enum class valueType {Null, Int, Float, String};


class PacketParser
{
private:
	std::map< char, std::pair< std::string, std::pair< valueType, std::string > > >	data;

public:
	PacketParser();
	~PacketParser();

	void	beginProcessing(std::istream &is);
	void 	extractData();
private:
	void	processSegment(std::string seg);
	void	readPacket();
	void	splitPacket();
	void	validateSegment();
	void	saveField(std::string &seg);
	void	findField();
	void	checkSegmentDataType();
	void	updateField(std::string &seg);
};


#endif //PACKETPARSER_PACKETPARSER_HPP
