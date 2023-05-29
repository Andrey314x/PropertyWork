#pragma once
#include "..\pugixml-1.13\src\pugixml.hpp"

using namespace pugi;
class Ixmlio
{
public:
	virtual void fromXML(xml_node xml) = 0;
	virtual void toXML(xml_node& node) = 0;
};

