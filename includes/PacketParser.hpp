//
// Created by mhonchar on 03.12.19.
//

#ifndef PACKETPARSER_PACKETPARSER_HPP
# define PACKETPARSER_PACKETPARSER_HPP

# include <iostream>
# include <map>
# include <sstream>
# include "Exceptions.hpp"
# include "AList.hpp"


enum class OperatioType {Null, Save, Assign, Add, Sub};


class PacketParser
{

public:
	explicit PacketParser();
	~PacketParser();
	void	beginProcessing(std::istream &is);
	void	showData();

private:
	std::string	packetSplit(const std::string &packet, size_t &pos);
	void		processSegment(const int key, const std::string &value, const __ItemValueType value_tyep, const OperatioType opt);
	void		saveField(const int key, const std::string &value);
	void		updateField(const int key, const std::string &value, const __ItemValueType value_type, const OperatioType opt);

	void		assignValue(const int key, const std::string &value, const __ItemValueType value_type);
	void		addValues(const int key, const std::string &value, const __ItemValueType value_type);
	void		subValues(const int key, const std::string &value, const __ItemValueType value_type);

private:
	AList data;
	static const size_t reservedLen;
};


#endif //PACKETPARSER_PACKETPARSER_HPP
