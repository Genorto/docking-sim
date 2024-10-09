#include <iostream>
#include "../../includes/ship/ship.h"

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

bool Ship::isHovered(sf::Vector2i cursor_pos) {
	return is_shown_ && (cursor_pos.x >= x_ && cursor_pos.x <= x_ + size_x_) && (cursor_pos.y >= y_ && cursor_pos.y <= y_ + size_y_);
}
	
void Ship::SetType(ShipType type) {
	type_ = type;
}

void Ship::set_weight(int weight) {
	weight_ = weight;
}

int Ship::get_weight() {
	return weight_;
}

void Ship::set_arrival_rejection(int rej) {
	arrival_rejection_ = rej;
}

int Ship::get_arrival_rejection() {
	return arrival_rejection_;
}

void Ship::SetArrivalTime(std::pair<int, int> data) {
	arrival_time_ = data;
}

std::pair<int, int> Ship::get_arrival_time() {
	return arrival_time_;
}

void Ship::set_ship_name(std::string name) {
	ship_name_ = name;
}

std::string Ship::get_ship_name() {
	return ship_name_;
}

ShipType Ship::get_type() {
	return type_;
}

void Ship::SetPos(double x, double y) {
	x_ = x;
	y_ = y;
	start_x_ = x;
	start_y_ = y;
	end_x_ = x;
	end_y_ = y;
}

std::pair<double, double> Ship::GetPos() {
	return { x_, y_ };
}

void Ship::SetStartPos(double x, double y) {
	start_x_ = x;
	start_y_ = y;
}

std::pair<double, double> Ship::GetStartPos() {
	return { start_x_, start_y_ };
}

void Ship::SetEndPos(double x, double y) {
	end_x_ = x;
	end_y_ = y;
}

std::pair<double, double> Ship::GetEndPos() {
	return { end_x_, end_y_ };
}

void Ship::Animate(double time, int fps, double duration) {
	int step = time * (double)fps;
	x_ = start_x_ + step * (abs(end_x_ - start_x_) / (fps * duration));
	y_ = start_y_ - step * (abs(end_y_ - start_y_) / (fps * duration));
	if (time >= duration) {
		start_x_ = x_;
		start_y_ = y_;
		end_x_ = x_;
		end_y_ = y_;
	}
}

void Ship::SetArrivalTime(std::pair<int, int> data) {
	arrival_time_ = data;
}

void Ship::SetSize(double size_x, double size_y) {
	size_x_ = size_x;
	size_y_ = size_y;
}

std::pair<double, double> Ship::GetSize() {
	return { size_x_, size_y_ };
}

void Ship::SetModel(std::string path) {
	if (!model_.loadFromFile(path)) model_.loadFromFile("assets/sprites/error.png");
}

void Ship::Show() {
	is_shown_ = true;
}

void Ship::Hide() {
	is_shown_ = false;
}

void Ship::Draw(sf::RenderWindow*& window) {
	sf::Sprite ship(model_);
	ship.setPosition(sf::Vector2f(x_, y_));
	ship.setScale(size_x_ / model_.getSize().x, size_y_ / model_.getSize().y);
	if (is_shown_) window->draw(ship);
}

