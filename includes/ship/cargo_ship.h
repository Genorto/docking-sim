#pragma once
#include "ship.h"

class CargoShip : public Ship {
public:
	CargoShip();
	CargoShip(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	~CargoShip() = default;
	virtual std::vector<std::string*> GetInfo() override;
};