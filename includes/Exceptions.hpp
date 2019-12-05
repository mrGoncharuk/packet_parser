//
// Created by mhonchar on 04.12.19.
//

#ifndef PACKET_PARSER_EXCEPTIONS_HPP
# define PACKET_PARSER_EXCEPTIONS_HPP

# include <exception>
# include <string>
//# include <limits>
//# include <iostream>
# include <stdexcept>

# include "AList.hpp"


class KeyValueNotFoundException : public std::exception
{
public:
	explicit KeyValueNotFoundException();
	virtual	const char *what() const throw();
	virtual ~KeyValueNotFoundException();
private:
	std::string msg;
};


class UndefinedEndOfStringException : public std::exception
{
public:
	explicit UndefinedEndOfStringException(const std::string &segment);
	virtual	const char *what() const throw();
	virtual ~UndefinedEndOfStringException();
private:
	std::string msg;
};

class UnsupportedKeyValueException : public std::exception
{
public:
	explicit UnsupportedKeyValueException(const char key);
	virtual	const char *what() const throw();
	virtual ~UnsupportedKeyValueException();
private:
	std::string msg;
};

class BadExspressionException : public std::exception
{
public:
	explicit BadExspressionException(const std::string &segment);
	virtual	const char *what() const throw();
	virtual ~BadExspressionException();
private:
	std::string msg;
};

class ReDefinitionException : public std::exception
{
public:
	explicit ReDefinitionException(const std::string &element, const std::string &newdef);
	virtual	const char *what() const throw();
	virtual ~ReDefinitionException();
private:
	std::string msg;
};

class UnrecognizedElementException : public std::runtime_error
{
public:
	explicit UnrecognizedElementException(const std::string &msg, const char key);
	virtual	const char *what() const throw();
	virtual ~UnrecognizedElementException();
private:
	std::string msg;
};

class ModifyingBeforeInitializationException : public std::runtime_error
{
public:
	explicit ModifyingBeforeInitializationException(const std::string &value, const char key);
	virtual	const char *what() const throw();
	virtual ~ModifyingBeforeInitializationException();
private:
	std::string msg;
};

class BadTypeException : public std::runtime_error
{
public:
	explicit BadTypeException(const char key, const __ItemValueType var_type, const __ItemValueType val_type);
	virtual	const char *what() const throw();
	virtual ~BadTypeException();
private:
	std::string msg;
};

class UnsupportedOperationException : public std::runtime_error
{
public:
	explicit UnsupportedOperationException(const std::string &msg, const char key, __ItemValueType type);
	virtual	const char *what() const throw();
	virtual ~UnsupportedOperationException();
private:
	std::string msg;
};


#endif //PACKET_PARSER_EXCEPTIONS_HPP
