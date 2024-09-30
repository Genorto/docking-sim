#pragma once
#include "Ship.h"

class CargoShip :protected Ship {
public:
	CargoShip();
	CargoShip(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	~CargoShip() = default;
};