#include <iostream>
#include "Ship.h"

Ship::Ship() : weight_(0), arrival_time_({ 0, 0 }), arrival_rejection_(0), fine_(0) {}

Ship::Ship(int weight, std::pair<int, int> arrival_time, std::string ship_name) {
	weight_ = weight;
	arrival_time_ = arrival_time;
	ship_name_ = ship_name;
	arrival_rejection_ = rand() % 11 - 2;
	fine_ = rand() % 20;
}

Ship::Ship(const Ship& other) {
	weight_ = other.weight_;
	arrival_time_ = other.arrival_time_;
	ship_name_ = other.ship_name_;
	arrival_rejection_ = other.arrival_rejection_;
	type_ = other.type_;
}

Ship::Ship(Ship&& other) {
		weight_ = std::move(other.weight_);
		arrival_time_ = std::move(other.arrival_time_);
		ship_name_ = std::move(other.ship_name_);
		arrival_rejection_ = std::move(other.arrival_rejection_);
		type_ = std::move(other.type_);
}

Ship& Ship::operator= (const Ship& other) {
	weight_ = other.weight_;
	arrival_time_ = other.arrival_time_;
	ship_name_ = other.ship_name_;
	arrival_rejection_ = other.arrival_rejection_;
	return *this;
}
	
void Ship::SetType(ShipType type) {
	type_ = type;
}

int Ship::get_weight() {
	return weight_;
}

int Ship::get_arrival_rejection() {
	return arrival_rejection_;
}

std::pair<int, int> Ship::get_arrival_time() {
	return arrival_time_;
}

std::string Ship::get_ship_name() {
	return ship_name_;
}

ShipType Ship::get_type() {
	return type_;
}