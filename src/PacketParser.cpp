//
// Created by mhonchar on 03.12.19.
//

#include "../includes/PacketParser.hpp"




PacketParser::PacketParser()
{}
PacketParser::~PacketParser()
{}

void	PacketParser::showData()
{
	for (auto it = data.begin(); it != data.end(); it++)
		std::cout << it->second.first << '(' << it->first << "): " << it->second.second.second << std::endl;
}

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
	data[seg[0]].second.first = valueType::Null;
}

void	PacketParser::updateField(std::string &seg)
{
	if (data.find(seg[0]) == data.end())
		throw "Modyfing undeclared element.";

	char op = recognizeOperator(seg);
	std::string value = extractValue(seg, op);
	valueType val_type = recognizeType(value);
	if (data[seg[0]].second.first == valueType::Null)
	{
		if ((op != '\0' && op != '='))
			throw "Modifying unitilalized value.";
		data[seg[0]].second.first = val_type;
		data[seg[0]].second.second = value;
		return;
	}
	if (data[seg[0]].second.first != val_type)
		throw "Type error.";

	if (op == '\0' || op == '=')
	{
		data[seg[0]].second.second = value;
	}
	else if (op == '+')
	{
		addValues(value, seg[0]);
	}
	else
		subValues(value, seg[0]);
}

void	PacketParser::addValues(const std::string &value, const char key)
{
	if (data[key].second.first == valueType::Int)
	{
		int result = std::stoi(data[key].second.second) + std::stoi(value);
		data[key].second.second = std::to_string(result);
	}
	else if (data[key].second.first == valueType::Float)
	{
		float result = std::stof(data[key].second.second) + std::stof(value);
		data[key].second.second = std::to_string(result);
	}
	else
	{
		data[key].second.second += value;
	}
}

void	PacketParser::subValues(const std::string &value, const char key)
{
	if (data[key].second.first == valueType::Int)
	{
		int result = std::stoi(data[key].second.second) - std::stoi(value);
		data[key].second.second = std::to_string(result);
	}
	else if (data[key].second.first == valueType::Float)
	{
		float result = std::stof(data[key].second.second) - std::stof(value);
		data[key].second.second = std::to_string(result);
	}
	else
	{
		throw "Unsuported operation of substraction on string!";
	}
}

char	PacketParser::recognizeOperator(const std::string &seg)
{
	if ((seg[1] == '+') || (seg[1] == '-') || (seg[1] == '='))
		return seg[1];
	else
		return '\0';
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


valueType	PacketParser::recognizeType(const std::string &value)
{
	int i = 0;
	int j = value.length() - 1;
	bool flagFloat = false;

	if (i == j && !(value[i] >= '0' && value[i] <= '9'))
		return valueType::String;

	if (value[i] != '.' && value[i] != '+'
		&& value[i] != '-' && !(value[i] >= '0' && value[i] <= '9'))
		return valueType::String;

	for (i; i <= j; i++)
	{
		if (value[i] != 'e' && value[i] != '.'
			&& value[i] != '+' && value[i] != '-'
			&& !(value[i] >= '0' && value[i] <= '9'))
			return valueType::String;

		if (value[i] == '.')
		{
			if (flagFloat == true)
				return valueType::String;
			if (i + 1 > value.length())
				return valueType::String;
			if (!(value[i + 1] >= '0' && value[i + 1] <= '9'))
				return valueType::String;
			flagFloat = true;
		}
		else if (value[i] == 'e')
		{
			flagFloat = true;
			if (!(value[i - 1] >= '0' && value[i - 1] <= '9'))
				return valueType::String;
			if (i + 1 > value.length())
				return valueType::String;
			if (value[i + 1] != '+' && value[i + 1] != '-'
				&& (value[i + 1] >= '0' && value[i] <= '9'))
				return valueType::String;
		}
	}
	if (flagFloat)
		return valueType::Float;
	return valueType::Int;
}
