//
// Created by mhonchar on 03.12.19.
//

#include "../includes/PacketParser.hpp"
#include <iomanip>
PacketParser::PacketParser()
{

}
PacketParser::~PacketParser()
{}

void	PacketParser::showData()
{
	for (char i = 'A'; i <= 'Z'; i++)
	{
		if (data[i].get_type() != IVT_NULL)
			std::cout << data[i]["name"] << '(' << i << "): " << data[i]["value"] << std::endl;
	}
}

std::string	PacketParser::packetSplit(const std::string &packet, size_t &pos)
{
	bool	isQuoteExist = false;
	size_t	len = 0;
	size_t	begin = pos;

	while ((packet[pos] != ' ' || isQuoteExist) && packet[pos] != '\0')
	{
		if (packet[pos] == '"')
			isQuoteExist = !isQuoteExist;
		pos++;
	}
	len = pos - begin;
	if (packet[pos] == '\0')
	{
		if (isQuoteExist)
			throw UndefinedEndOfStringException(packet.substr(begin, len));
		else
			pos = std::string::npos;
	}
	else
		pos++;
	return packet.substr(begin, len);
}


void	PacketParser::beginProcessing(std::istream &is)
{
	std::string packet;
	size_t		pos = 0;

	while (std::getline(is, packet))
	{
		while (pos != std::string::npos)
		{
			std::string segment = packetSplit(packet, pos);
			processSegment(segment);
		}
		pos = 0;
	}
}

void	PacketParser::processSegment(const std::string &seg)
{
	if (seg.find(':') != std::string::npos)
		saveField(seg);
	else
		updateField(seg);
}

void	PacketParser::saveField(const std::string &seg)
{
	if (data[seg[0]].get_type() == IVT_NULL)
		data[seg[0]] = new AList;
	if (seg.length() < 3 || !(seg[0] >='A' && seg[0] <= 'Z') || seg[1] != ':')
		throw BadExspressionException(seg);
	if (data[seg[0]]["name"].get_value().sValue != NULL)
		throw ReDefinitionException(std::string(data[seg[0]]["name"].get_value().sValue), seg);		//changed

	size_t quote_start = seg.find('"');
	std::string field_name;
	if (quote_start != std::string::npos)
		field_name = seg.substr(quote_start, seg.length() - 1);
	else
		field_name = seg.substr(2, seg.length());
	data[seg[0]]["name"] = field_name.c_str();		//changed
}

void	PacketParser::updateField(const std::string &seg)
{
	if (data[seg[0]]["name"].get_value().sValue == NULL)
		throw UnrecognizedElementException(seg);

	char op = recognizeOperator(seg);
	std::string value = extractValue(seg, op);
	__ItemValueType val_type = recognizeType(value);
	if (data[seg[0]]["value"].get_type() == IVT_NULL)
	{
		if ((op != '\0' && op != '='))
			throw ModifyingBeforeInitializationException(seg);
		if (val_type == IVT_INT)
			data[seg[0]]["value"] = std::stoi(value);
		else if (val_type == IVT_FLOAT)
			data[seg[0]]["value"] = std::stof(value);
		else
			data[seg[0]]["value"] = removeQuotes(value).c_str();
		return;
	}
	if (data[seg[0]]["value"].get_type() != val_type)
		throw BadTypeException(data[seg[0]]["value"].get_type(), val_type);

	if (op == '\0' || op == '=')
		assignValue(value, seg[0]);
	else if (op == '+')
		addValues(value, seg[0]);
	else
		subValues(value, seg[0]);
}

std::string	PacketParser::extractValue(const std::string &seg, const char op)
{
	std::string value;
	size_t beg;
	if (op == '\0')
		beg = 1;
	else
		beg = 2;
	return seg.substr(beg, seg.length());
}

__ItemValueType	PacketParser::recognizeType(const std::string &value)
{
	int i = 0;
	int j = value.length() - 1;
	bool flagFloat = false;

	if (i == j && !(value[i] >= '0' && value[i] <= '9'))
		return IVT_STRING;

	if (value[i] != '.' && value[i] != '+'
		&& value[i] != '-' && !(value[i] >= '0' && value[i] <= '9'))
		return IVT_STRING;

	while (i <= j)
	{
		if (value[i] != 'e' && value[i] != '.'
			&& value[i] != '+' && value[i] != '-'
			&& !(value[i] >= '0' && value[i] <= '9'))
			return IVT_STRING;

		if (value[i] == '.')
		{
			if (flagFloat)
				return IVT_STRING;
			if (i + 1 > static_cast<int>(value.length()))
				return IVT_STRING;
			if (!(value[i + 1] >= '0' && value[i + 1] <= '9'))
				return IVT_STRING;
			flagFloat = true;
		}
		else if (value[i] == 'e')
		{
			flagFloat = true;
			if (!(value[i - 1] >= '0' && value[i - 1] <= '9'))
				return IVT_STRING;
			if (i + 1 > static_cast<int>(value.length()))
				return IVT_STRING;
			if (value[i + 1] != '+' && value[i + 1] != '-'
				&& (value[i + 1] >= '0' && value[i] <= '9'))
				return IVT_STRING;
		}
		i++;
	}
	if (flagFloat)
		return IVT_FLOAT;
	return IVT_INT;
}

char	PacketParser::recognizeOperator(const std::string &seg)
{
	if ((seg[1] == '+') || (seg[1] == '-') || (seg[1] == '='))
		return seg[1];
	else
		return '\0';
}

void	PacketParser::assignValue(const std::string &value, const char key)
{
	if (data[key]["value"].get_type() == IVT_INT)
		data[key]["value"] = std::stoi(value);
	else if (data[key]["value"].get_type() == IVT_FLOAT)
		data[key]["value"] = std::stof(value);
	else
		data[key]["value"] = value.c_str();
}

void	PacketParser::addValues(const std::string &value, const char key)
{
	if (data[key]["value"].get_type() == IVT_INT)
	{
		int result = data[key]["value"].get_value().iValue + std::stoi(value);
		data[key]["value"] = result;
	}
	else if (data[key]["value"].get_type() == IVT_FLOAT)
	{
		float result = data[key]["value"].get_value().fValue + std::stof(value);
		data[key]["value"] = result;
	}
	else
	{
		data[key]["value"] = (removeQuotes(value) + data[key]["value"].get_value().sValue).c_str();
	}
}

void	PacketParser::subValues(const std::string &value, const char key)
{
	if (data[key]["value"].get_type() == IVT_INT)
	{
		int result = data[key]["value"].get_value().iValue - std::stoi(value);
		data[key]["value"] = result;
	}
	else if (data[key]["value"].get_type() == IVT_FLOAT)
	{
		float result = data[key]["value"].get_value().fValue - std::stof(value);
		data[key]["value"] = result;
	}
	else
	{
		throw UnsupportedOperationException("Subtraction of strings is unsupported!");
	}
}

std::string		PacketParser::removeQuotes(const std::string &val)
{
		if (val[0] == '"' && val[val.length() - 1] == '"')
			return val.substr(1, val.length() - 2);
		else
			return val;
}
