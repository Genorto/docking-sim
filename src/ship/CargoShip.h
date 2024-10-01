#pragma once
#include "Ship.h"

class CargoShip : public Ship {
public:
	CargoShip();
	CargoShip(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	~CargoShip() = default;
};