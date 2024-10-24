#include "../../includes/ship/ship.h"

Ship::Ship() : weight_(0), arrival_time_({ 0, 0 }), arrival_rejection_(0) {}

Ship::Ship(int weight, std::pair<int, int> arrival_time, std::string ship_name) {
	weight_ = weight;
	arrival_time_ = arrival_time;
	ship_name_ = ship_name;
	arrival_rejection_ = rand() % 11 - 2;
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
	return (animation_ != Animation::Invisible) && (cursor_pos.x >= x_ && cursor_pos.x <= x_ + size_x_) && (cursor_pos.y >= y_ && cursor_pos.y <= y_ + size_y_);
}
	
void Ship::SetType(ShipType type) {
	type_ = type;
}

void Ship::SetWeight(int weight) {
	weight_ = weight;
}

int Ship::GetWeight() {
	return weight_;
}

void Ship::SetShipName(std::string name) {
	ship_name_ = name;
}

std::string Ship::GetName() {
	return ship_name_;
}

void Ship::SetArrivalRejection(int rej) {
	arrival_rejection_ = rej;
}

int Ship::GetArrivalRejection() {
	return arrival_rejection_;
}

void Ship::SetArrivalTime(std::pair<int, int> data) {
	arrival_time_ = data;
}

std::pair<int, int> Ship::GetArrivalTime() {
	return arrival_time_;
}

ShipType Ship::GetType() {
	return type_;
}

void Ship::SetPos(double x, double y) {
	x_ = x;
	y_ = y;
	start_x_ = x;
	start_y_ = y;
	end_x_ = x;
	end_y_ = y;
	if (animation_ == Animation::FadeOut) {
		animation_ = Animation::Invisible;
	} else if (animation_ == Animation::FadeIn) {
		animation_ = Animation::Visible;
	} else if (animation_ == Animation::Unload) {
		rotation_ = -90;
		animation_ = Animation::Visible;
	}
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

double RadToAngle(double rad) {
	return (180 * rad) / 3.14159265358979323846;
}

void Ship::Animate(double time, int fps, double duration) {
	int step = time * (double)fps;
	
	if (animation_ == Animation::Unload) {
		rotation_ = -90 * (time / duration);
	} else if (animation_ == Animation::FadeIn) {
		rotation_ = 0;
	} 

	x_ = start_x_ + step * ((end_x_ - start_x_) / (fps * duration));
	y_ = start_y_ + step * ((end_y_ - start_y_) / (fps * duration));

	if (animation_ == Animation::FadeIn) {
		color_ = sf::Color(255, 255, 255, step * (255 / ((double)fps * duration)));
	} else if (animation_ == Animation::FadeOut) {
		color_ = sf::Color(255, 255, 255, 255 - step * (255 / ((double)fps * duration)));
	} else if (animation_ == Animation::Visible || animation_ == Animation::Unload) {
		color_ = sf::Color(255, 255, 255, 255);
	} else {
		color_ = sf::Color(255, 255, 255, 0);
	}

	if (time >= duration) {
		SetPos(end_x_, end_y_);
	}
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
	animation_ = Animation::Visible;
}

void Ship::Hide() {
	animation_ = Animation::Invisible;
}

void Ship::FadeIn() {
	animation_ = Animation::FadeIn;
}

void Ship::FadeOut() {
	animation_ = Animation::FadeOut;
}

void Ship::Unload() {
	animation_ = Animation::Unload;
}

void Ship::Draw(sf::RenderWindow*& window) {
	sf::Sprite ship(model_);
	ship.setScale(size_x_ / model_.getSize().x, size_y_ / model_.getSize().y);
	ship.setOrigin(ship.getLocalBounds().width / 2, ship.getLocalBounds().height / 2);
	ship.setPosition(sf::Vector2f(x_ + ship.getLocalBounds().width / 2, y_ + ship.getLocalBounds().height / 2));
	ship.setRotation(rotation_);
	ship.setColor(color_);
	window->draw(ship);
}
