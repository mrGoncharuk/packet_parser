//
// Created by mhonchar on 03.12.19.
//

#ifndef PACKETPARSER_PACKETPARSER_HPP
# define PACKETPARSER_PACKETPARSER_HPP

# include <iostream>
# include <map>
# include <sstream>
# include "Exceptions.hpp"



class PacketParser
{
public:
	explicit PacketParser();
	~PacketParser();
	void	beginProcessing(std::istream &is);
	void	showData();
private:
	std::string	packetSplit(const std::string &packet, size_t &pos);
	void		processSegment(const std::string &seg);
	void		saveField(const std::string &seg);
	void		updateField(const std::string &seg);
	std::string	extractValue(const std::string &seg, const char op);
	valueType	recognizeType(const std::string &value);
	char		recognizeOperator(const std::string &seg);
	void		addValues(const std::string &value, const char key);
	void		subValues(const std::string &value, const char key);
	std::string	removeQuotes(const std::string &val);

private:
	std::map< char, std::pair< std::string, std::pair< valueType, std::string > > >	data;
};


#endif //PACKETPARSER_PACKETPARSER_HPP
