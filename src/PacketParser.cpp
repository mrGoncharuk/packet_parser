//
// Created by mhonchar on 03.12.19.
//

#include "../includes/PacketParser.hpp"
#include <iomanip>

const size_t PacketParser::reservedLen = 1024;

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

void	PacketParser::beginProcessing(std::istream &is)
{
	int			ch;
	std::string	value;
	OperatioType opt = OperatioType::Null;
	__ItemValueType	value_type = IVT_INT;
	bool	isQuoteExist = false;
	bool 	isSigned = false;
	int		key = -1;

	value.reserve(PacketParser::reservedLen);
	while (is.good() && (ch = is.get()) != -1)
	{
		switch(ch)
		{
			case '+':
			{
				if (opt == OperatioType::Null)
					opt = OperatioType::Add;
				else if (value_type != IVT_STRING && !isSigned && value.length() == 0)
				{
					isSigned = true;
					value.push_back(ch);
				}
				else
					value_type = IVT_STRING;
				break;
			}
			case '-':
			{
				if (opt == OperatioType::Null)
					opt = OperatioType::Sub;
				else if (value_type != IVT_STRING && !isSigned && value.length() == 0)
				{
					isSigned = true;
					value.push_back(ch);
				}
				else
					value_type = IVT_STRING;
				break;
			}
			case ':':
			{
				opt = OperatioType::Save;
				break;
			}

			case '=':
			{
				opt = OperatioType::Assign;
				break;
			}
			case '.':
			{
				if (value_type == IVT_FLOAT)
					value_type = IVT_STRING;
				else
					value_type = IVT_FLOAT;
				value.push_back(ch);
				break;
			}
			case '"':
			{
				isQuoteExist = !isQuoteExist;
				value_type = IVT_STRING;
				break;
			}
			case ' ':
			case '\n':
			{
				if (isQuoteExist)
				{
					if (ch == '\n')
						throw UndefinedEndOfStringException(value);
					value.push_back(ch);
					break;
				}
				processSegment(key, value, value_type, opt);
				value_type = IVT_INT;
				isSigned = false;
				opt = OperatioType::Null;
				isQuoteExist = false;
				value.clear();
				key = -1;
				break;
			}
			default:
			{
				if (key == -1)
				{
					if (ch >='A' && ch <= 'Z')
					{
						key = ch;
						break;
					}
					else
						throw UnsupportedKeyValueException(static_cast<char>(ch));
				}
				if (opt == OperatioType::Null && key != -1)
					opt = OperatioType::Assign;
				if (!(ch >= '0' && ch <= '9'))
					value_type = IVT_STRING;
				value.push_back(ch);
				break;
			}
		}
	}
}

void	PacketParser::processSegment(const int key, const std::string &value, const __ItemValueType value_type, const OperatioType opt)
{
	if (opt == OperatioType::Save)
		saveField(key, value);
	else
		updateField(key, value, value_type, opt);
}

void	PacketParser::saveField(const int key, const std::string &value)
{
	if (data[key].get_type() == IVT_NULL)
		data[key] = new AList;
	if (data[key]["name"].get_value().sValue != NULL)
		throw ReDefinitionException(std::string(data[key]["name"].get_value().sValue), value);

	data[key]["name"] = value.c_str();
}

void	PacketParser::updateField(const int key, const std::string &value, const __ItemValueType value_type, const OperatioType opt)
{
	if (data[key].get_value().aValue == NULL)
		throw UnrecognizedElementException("Using undeclared key.", static_cast<char>(key));

	if (data[key]["value"].get_type() == IVT_NULL)			// is value already initialized
	{
		if (opt != OperatioType::Assign)
			throw ModifyingBeforeInitializationException(value, static_cast<char>(key));

		if (value_type == IVT_INT)
			data[key]["value"] = std::stoi(value);
		else if (value_type == IVT_FLOAT)
			data[key]["value"] = std::stof(value);
		else if (value_type == IVT_STRING)
			data[key]["value"] = value.c_str();
		else
			throw UnrecognizedElementException("Unknown type of value.", static_cast<char>(key));
	}
	else
	{
		if (data[key]["value"].get_type() != value_type)
			throw BadTypeException(static_cast<char>(key), data[key]["value"].get_type(), value_type);
		if (opt == OperatioType::Assign)
			assignValue(key, value, value_type);
		else if (opt == OperatioType::Add)
			addValues(key, value, value_type);
		else if (opt == OperatioType::Sub)
			subValues(key, value, value_type);
		else
			throw BadExspressionException(value);
	}
}

void	PacketParser::assignValue(const int key, const std::string &value, const __ItemValueType value_type)
{
	if (value_type == IVT_INT)
		data[key]["value"] = std::stoi(value);
	else if (value_type == IVT_FLOAT)
		data[key]["value"] = std::stof(value);
	else if (value_type == IVT_STRING)
		data[key]["value"] = value.c_str();
}

void	PacketParser::addValues(const int key, const std::string &value, const __ItemValueType value_type)
{
	if (value_type == IVT_INT)
	{
		int result = data[key]["value"].get_value().iValue + std::stoi(value);
		data[key]["value"] = result;
	}
	else if (value_type == IVT_FLOAT)
	{
		float result = data[key]["value"].get_value().fValue + std::stof(value);
		data[key]["value"] = result;
	}
	else if (value_type == IVT_STRING)
		data[key]["value"] = (data[key]["value"].get_value().sValue + value).c_str();
	else
		throw UnsupportedOperationException("Unsupported addition on unknown type.", key, value_type);
}

void	PacketParser::subValues(const int key, const std::string &value, const __ItemValueType value_type)
{
	if (value_type == IVT_INT)
	{
		int result = data[key]["value"].get_value().iValue - std::stoi(value);
		data[key]["value"] = result;
	}
	else if (value_type == IVT_FLOAT)
	{
		float result = data[key]["value"].get_value().fValue - std::stof(value);
		data[key]["value"] = result;
	}
	else if (value_type == IVT_STRING)
		throw UnsupportedOperationException("Subtraction of strings is unsupported!", key, value_type);
	else
		throw UnsupportedOperationException("Unsupported substraction on unknown type.", key, value_type);
}
