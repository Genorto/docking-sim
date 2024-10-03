#include "../../includes/ship/tanker.h"

Tanker::Tanker(): Ship() { SetType(ShipType::Tanker); };

Tanker::Tanker(int weight, std::pair<int, int> arrival_time, std::string ship_name) :
	Ship(weight, arrival_time, ship_name) {
	SetType(ShipType::Tanker);
};

std::vector<std::string*> Tanker::GetInfo() {
    std::vector<std::string*> info;
    info.push_back(new std::string("Cargo ship"));
    info.push_back(new std::string(ship_name_));
    info.push_back(new std::string("Weight: " + std::to_string(weight_)));
    return info;
}
