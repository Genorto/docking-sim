#include "Tanker.h"

Tanker::Tanker(): Ship() { SetType(ShipType::Tanker); };

Tanker::Tanker(int weight, std::pair<int, int> arrival_time, std::string ship_name) :
	Ship(weight, arrival_time, ship_name) {
	SetType(ShipType::Tanker);
};

