#pragma once
#include "ship.h"

class Tanker : public Ship {
public:
	Tanker();
	Tanker(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	Tanker(const Tanker& other) : Ship(other) {}
	~Tanker() = default;
	virtual std::vector<std::string*> GetInfo() override;
};