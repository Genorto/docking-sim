#pragma once
#include <iostream>

enum class ShipType { CargoShip, Tanker };

class Ship {
public:
	Ship();
	Ship(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	Ship(Ship&& other);
	Ship(const Ship& other);
	Ship& operator= (const Ship& other);
	~Ship() = default;
	void SetType(ShipType type);
	void set_weight(int);
	int get_weight();
	int get_arrival_rejection();
	std::pair<int, int> get_arrival_time();
	std::string get_ship_name();
	ShipType get_type();

protected:
	// installed before the start
	int weight_;
	int fine_; //penalty for an hour of delay
	int arrival_rejection_; // delay (measured in days)
	std::pair<int, int> arrival_time_; // first - day, second - hour
	std::string ship_name_;
	ShipType type_;
	//  installed after the start
	int waiting_time_;
	int service_time_;
};