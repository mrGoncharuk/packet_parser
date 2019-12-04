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
public:
	explicit PacketParser();
	~PacketParser();
	void	beginProcessing(std::istream &is);
	void	showData();
private:
	void		processSegment(std::string seg);
	void		saveField(std::string &seg);
	valueType	recognizeType(const std::string &value);
	void		addValues(const std::string &value, const char key);
	void		subValues(const std::string &value, const char key);
	void		updateField(std::string &seg);
	std::string	extractValue(const std::string &seg, const char op);
	char		recognizeOperator(const std::string &seg);

private:
	std::map< char, std::pair< std::string, std::pair< valueType, std::string > > >	data;
};


#endif //PACKETPARSER_PACKETPARSER_HPP
