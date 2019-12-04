//
// Created by mhonchar on 04.12.19.
//

#include "../includes/AList.hpp"

ItemInfo& ItemInfo::operator[] (const int index)
{
	return (((AList&)(*m_value.aValue))[index]);
}

ItemInfo& ItemInfo::operator[] (const char* name)
{
	return (((AList&)(*m_value.aValue))[name]);
}
