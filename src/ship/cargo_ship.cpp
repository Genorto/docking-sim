#include "../../includes/ship/cargo_ship.h"

CargoShip::CargoShip() :Ship() { SetType(ShipType::CargoShip); };
	
CargoShip::CargoShip(int weight, std::pair<int, int> arrival_time, std::string ship_name) :
	Ship(weight, arrival_time, ship_name) {
	SetType(ShipType::CargoShip);
};

std::vector<std::string*> CargoShip::GetInfo() {
    std::vector<std::string*> info;
    info.push_back(new std::string("Cargo ship"));
    info.push_back(new std::string(ship_name_));
    info.push_back(new std::string(std::to_string(weight_)));
    return info;
}
