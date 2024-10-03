#include "../../includes/ship/cargo_ship.h"

CargoShip::CargoShip() :Ship() { SetType(ShipType::CargoShip); };
	
CargoShip::CargoShip(int weight, std::pair<int, int> arrival_time, std::string ship_name) :
		Ship(weight, arrival_time, ship_name) {
		SetType(ShipType::CargoShip);
	};

