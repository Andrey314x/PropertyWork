#pragma once
#include "json.hpp"

using nlohmann::json;

class Ijsonio {
public:
	virtual void fromJson(json json) = 0;
	virtual json toJson() = 0;
};
