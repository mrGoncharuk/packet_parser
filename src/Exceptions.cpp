//
// Created by mhonchar on 04.12.19.
//

#include "../includes/Exceptions.hpp"

BadExspressionException::BadExspressionException(const std::string &segment){
	msg = "Unrecognized expression was found [" + segment + "].";
}

ReDefinitionException::ReDefinitionException(const std::string &element, const std::string &newdef){
	msg = "Redefinition of element [" + element + "] by [" + newdef + "].";
}

UnrecognizedElementException::UnrecognizedElementException(const std::string &action)
	: runtime_error(action){
	msg = "Operation on undefined element [" + action +"].";
}

ModifyingBeforeInitializationException::ModifyingBeforeInitializationException(const std::string &segment)
	: runtime_error(segment){
	msg = "Modifying element before it initialization [" + segment +"].";
}

BadTypeException::BadTypeException(const valueType var_type, const valueType val_type)
	:runtime_error("Type error.")
{

	msg = "Modifying value of type [" + std::to_string(static_cast<int>(var_type)) +
			"] with type [" + std::to_string(static_cast<int>(val_type)) + "].";
}

UnsupportedOperationException::UnsupportedOperationException(const std::string &m)
	: runtime_error("Unsupported operation.")
	, msg(m)
	{ }

const char *BadExspressionException::what() const throw() { return msg.c_str(); }
const char *ReDefinitionException::what() const throw() { return msg.c_str(); }
const char *UnrecognizedElementException::what() const throw() { return msg.c_str(); }
const char *ModifyingBeforeInitializationException::what() const throw() { return msg.c_str(); }
const char *BadTypeException::what() const throw() { return msg.c_str(); }
const char *UnsupportedOperationException::what() const throw() { return msg.c_str(); }


BadExspressionException::~BadExspressionException() { }
ReDefinitionException::~ReDefinitionException() { }
UnrecognizedElementException::~UnrecognizedElementException() { }
ModifyingBeforeInitializationException::~ModifyingBeforeInitializationException() { }
BadTypeException::~BadTypeException() { }
UnsupportedOperationException::~UnsupportedOperationException() { }