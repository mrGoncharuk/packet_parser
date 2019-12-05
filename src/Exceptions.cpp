//
// Created by mhonchar on 04.12.19.
//

#include "../includes/Exceptions.hpp"

static std::string typeToStr(const __ItemValueType val_type)
{
	switch (val_type)
	{
		case (IVT_NULL) :
			return "NULL";
		case (IVT_BOOL) :
			return "BOOL";
		case (IVT_INT) :
			return "INT";
		case (IVT_FLOAT) :
			return "FLOAT";
		case (IVT_DOUBLE) :
			return "DOUBLE";
		case (IVT_STRING) :
			return "STRING";
		case (IVT_LIST) :
			return "LIST";
		case (IVT_OBJECT) :
			return "OBJECT";
		default:
			return "NULL";
	}

}

UnsupportedKeyValueException::UnsupportedKeyValueException(const char key){
	msg = "Unsupported key value: " + std::to_string(key);
}

UndefinedEndOfStringException::UndefinedEndOfStringException(const std::string &segment){
	msg = "Closing quote not found in packet. Value processed: '" + segment + "'.";
}

BadExspressionException::BadExspressionException(const std::string &segment){
	msg = "Unrecognized expression was found [" + segment + "].";
}

ReDefinitionException::ReDefinitionException(const std::string &element, const std::string &newdef){
	msg = "Redefinition of element [" + element + "] by [" + newdef + "].";
}

UnrecognizedElementException::UnrecognizedElementException(const std::string &m, const char key)
	: runtime_error(m){
	msg = m + " Key: " + key;
}

ModifyingBeforeInitializationException::ModifyingBeforeInitializationException(const std::string &value, const char key)
	: runtime_error("Modifying element before it initialization."){
	msg = "Modifying element before it initialization by value: " + value + "; With key: " + key;
}

BadTypeException::BadTypeException(const char key, const __ItemValueType var_type, const __ItemValueType val_type)
	:runtime_error("Type error."){

	msg = "Modifying value of type [" + typeToStr(var_type) + "] with type [" + typeToStr(val_type) + "]. With key: " + key;
}

UnsupportedOperationException::UnsupportedOperationException(const std::string &m, const char key, __ItemValueType type)
	: runtime_error("Unsupported operation."){
	msg = m + " Value key: " + key + " Value type: " + typeToStr(type);
}


const char *UndefinedEndOfStringException::what() const throw() { return msg.c_str(); }
const char *UnsupportedKeyValueException::what() const throw() { return msg.c_str(); }

const char *BadExspressionException::what() const throw() { return msg.c_str(); }
const char *ReDefinitionException::what() const throw() { return msg.c_str(); }
const char *UnrecognizedElementException::what() const throw() { return msg.c_str(); }
const char *ModifyingBeforeInitializationException::what() const throw() { return msg.c_str(); }
const char *BadTypeException::what() const throw() { return msg.c_str(); }
const char *UnsupportedOperationException::what() const throw() { return msg.c_str(); }


UndefinedEndOfStringException::~UndefinedEndOfStringException() { }
UnsupportedKeyValueException::~UnsupportedKeyValueException() { }
BadExspressionException::~BadExspressionException() { }
ReDefinitionException::~ReDefinitionException() { }
UnrecognizedElementException::~UnrecognizedElementException() { }
ModifyingBeforeInitializationException::~ModifyingBeforeInitializationException() { }
BadTypeException::~BadTypeException() { }
UnsupportedOperationException::~UnsupportedOperationException() { }