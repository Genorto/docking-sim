#pragma once
#include "Ship.h"

class Tanker :protected Ship {
public:
	Tanker();
	Tanker(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	~Tanker() = default;
};